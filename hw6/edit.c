#include "edit.h"

Edit *makeInsert( Document *doc, int ch )
{
  // Allocates memory for edit object and initializes virtual functions
  Edit *ins = ( Edit * )malloc( sizeof( Edit ) );
  ins->apply = apply;
  ins->undo = undo;
  ins->destroy = destroy;

  return ins;
}

Edit *makeDelete( Document *doc )
{
  // Allocates memory for edit object and initializes virtual functions
  Edit *del = ( Edit * )malloc( sizeof( Edit ) );
  del->apply = apply;
  del->undo = undo;
  del->destroy = destroy;

  return del;
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
  
}
