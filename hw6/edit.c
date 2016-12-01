#include "edit.h"

Edit *makeInsert( Document *doc, int ch )
{
  // Allocates memory for edit object and initializes virtual functions
  Modify *ins = ( Modify * )malloc( sizeof( Modify ) );
  ins->apply = insert;
  ins->undo = undo;
  ins->destroy = destroy;

  // Sets insert position in document and sets the given character
  ins->cRow = doc->cRow;
  ins->cCol = doc->cCol;
  ins->ch = ch;

  return ( Edit * )ins;
}

Edit *makeDelete( Document *doc )
{
  // Checks if delete operation is possible
  if( doc->cRow > 0 ||
      doc->cCol > 0 ) {
    // Allocates memory for edit object and initializes virtual functions
    Modify *del = ( Modify * )malloc( sizeof( Modify ) );
    del->apply = delete;
    del->undo = undo;
    del->destroy = destroy;

    // Sets delete position in document
    del->cRow = doc->cRow;
    del->cCol = doc->cCol - 1;
    return (Edit *) del;
  }
  else
    return NULL;
}

void initHistory( History *hist )
{
  // Initializes array of pointers
  for( int i = 0; i < HIST_SIZE; i++ ) {
    hist->undo[i] = NULL;
    hist->redo[i] = NULL;
  }
  // Sets initial length of arrays
  hist->ulen = 0;
  hist->rlen = 0;
}

void clearHistory( History *hist )
{
  for( int i = 0; i < HIST_SIZE; i++ ) {
    destroy(hist->undo[i]);
    destroy(hist->redo[i]);
  }
}

void applyEdit( History *hist, Document *doc, Edit *edit )
{
  // Pointer to edit operation
  Edit *op = hist->undo[ hist->ulen ];
  // Perform apply operation
  op->apply( op, doc );
  // Add edit to undo history
  hist->undo[ hist->ulen ++ ] = edit;
}

bool undoEdit( History *hist, Document *doc )
{
  if( hist->ulen == 0 )
    return false;
  else {
    // Pointer to undo operation
    Edit *op = hist->undo[ hist->ulen ];
    // Perform undo operation
    op->undo( op, doc );
    // Move undo to redo history
    hist->redo[ hist->rlen ++ ] = op;
    hist->undo[ hist->ulen -- ] = NULL;
    return true;
  }
}

bool redoEdit( History *hist, Document *doc )
{
  if( hist->rlen == 0 )
    return false;
  else {
    // Pointer to redo operation
    Edit *op = hist->redo[ hist->ulen ];
    // Perform redo operation
    op->undo( op, doc );
    // Move redo to undo history
    hist->undo[ hist->ulen ++ ] = op;
    hist->redo[ hist->rlen -- ] = NULL;
    return true;
  }
}
void delete( Edit *edit, Document *doc )
{
  Modify *delete = (Modify *) edit;
  Line *str = doc->lines[ delete->cRow ];
  if( delete->cCol >= 0 ) {
      memmove( str->text + delete->cCol, str->text + delete->cCol + 1,
               str->len - delete->cCol );
      str->len --;
      doc->cCol = delete->cCol;
    }
    else {
      Line *prev = doc->lines[ delete->cRow - 1 ];
      // Reallocates memory if necessary
      if( prev->cap <= str->len + prev->len ) {
        prev->cap = str->len + prev->len + 1 ;
        prev->text = ( char * )realloc( prev->text, prev->cap );
      }
      // Appends text to previous line
      prev->len += str->len; 
      prev->text = strcat( prev->text, str->text );
      // Frees the removed line
      freeLine( str );
      // Removes the line from the document
      memmove( doc->lines + delete->cRow , doc->lines + delete->cRow + 1,
               doc->len - delete->cRow );
      doc->len --;
      // Update Document cursor position
      doc->cCol = doc->lines[ delete->cRow ]->len;
      // Do something with apply cursor position
      // ...

    }
}
void insert( Edit *edit, Document *doc )
{
  Modify *insert = (Modify *) edit;
}
