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
  ins->isDelete = false;

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
    del->ch = 0;
    del->isDelete = true;
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
    hist->undo[i]->destroy( hist->undo[i] );
    hist->redo[i]->destroy( hist->redo[i] );
  }
  hist->ulen = 0;
  hist->rlen = 0;
}

void applyEdit( History *hist, Document *doc, Edit *edit )
{
  // Pointer to edit operation
  Edit *op = hist->undo[ hist->ulen ];
  // Perform apply operation
  op->apply( op, doc );
    
  // Add edit to undo history
  if( hist->ulen == HIST_SIZE ) {
    // Frees oldest undo
    hist->undo[0]->destroy( hist->undo[0] );
    for( int i = 1; i < hist->ulen; i++ )
      hist->undo[ i - 1 ] = hist->undo[ i ];
    hist->undo[ hist->ulen ] = edit;
  }
  else
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
  // Checks if character deleted is newline or not
  if( delete->cCol >= 0 ) {
    // Store deleted character
    delete->ch = str->text[ delete->cCol ];
    // Remove character
    memmove( str->text + delete->cCol, str->text + delete->cCol + 1,
             str->len - delete->cCol );
    str->len --;
    // Update document cursor position
    if( delete->isDelete )
      moveCursor( doc, CursorLeft);
    else
      doc->cCol = delete->cCol;
  }
  else {
    Line *prev;
    // Sets ch to newline for undo purposes
    delete->ch = '\n';
    // Sets previous line to a pointer
    if( delete->cRow == 0 ) {
      prev = str;
      str = doc->lines[ 1 ];
    }
    else
      prev = doc->lines[ delete->cRow - 1 ];
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
    if( delete->cRow == 0 ){
      for( int i = 1; i < doc->len; i++ )
        doc->lines[i] = doc->lines[i+1];
    }
    else {
      for( int i = delete->cRow; i < doc->len - delete->cRow; i++ )
        doc->lines[i] = doc->lines[i+1];
    }
    doc->len --;
    // Update document cursor position
    moveCursor( doc, CursorUp);
    doc->cCol = prev->len - str->len;
    delete->cRow = doc->cRow;
    delete->cCol = doc->cCol;
  }
}
void insert( Edit *edit, Document *doc )
{
  Modify *insert = (Modify *) edit;
  Line *str = doc->lines[ insert->cRow ];
  // Checks if insert is a newline character or not
  if( insert->ch == '\n' ) {
    // Reallocates space for document lines
    if( doc->cap <= ++ doc->len ) {
      doc->cap *= 2;
      doc->lines = ( Line ** )realloc( doc->lines, doc->cap );
    }
    // Makes space for inserted line
    for( int i = doc->len; i > insert->cRow; i-- )
      doc->lines[ i ] = doc->lines[ i - 1 ];
    // Initialize new line
    doc->lines[ insert->cRow + 1 ] = (Line *)malloc( sizeof( Line ) );
    Line *next = doc->lines[ insert->cRow + 1 ];
    next->cap = str->len - insert->cCol + 1;
    next->len = next->cap - 1;
    next->text = (char *)malloc( next->cap );
    // Move part of the line to new line
    memcpy( next->text, str->text + insert->cCol,
             str->len - insert->cCol );

    str->text[ insert->cCol ] = '\0';
    str->len = insert->cCol;
    next->text[ next->len ] = '\0';
    insert->cCol = -1;

    // Update document cursor position
    moveCursor( doc, CursorDown);
    doc->cCol = 0;
  }
  else {
    if( str->cap <= ++ str->len ) {
      str->cap *= 2;
      str->text = ( char * )realloc( str->text, str->cap );
    }
    // Makes space for inserted character
    for( int i = str->len; i >= insert->cCol; i-- )
      str->text[ i ] = str->text[ i - 1 ];
    // Insert character at position
    str->text[ insert->cCol ] = insert->ch;
    // Update document cursor position
    doc->cCol = insert->cCol;
    doc->cRow = insert->cRow;
    moveCursor( doc, CursorRight);
  }
}
void undo( Edit *edit, Document *doc )
{
  Modify *undo = (Modify *) edit;
  undo->isDelete ? insert( edit, doc ) : delete( edit, doc );
  undo->isDelete = !undo->isDelete;
}
void destroy( Edit *edit )
{
  Modify *destroy = (Modify *) edit;
  free( destroy );
}