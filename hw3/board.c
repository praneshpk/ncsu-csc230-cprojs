#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool winner( int rows, int cols, char board[ rows ][ cols ],
             int startRow, int startCol, int dRow, int dCol ) {
  // Number of X and O symbols in this sequence of locations
  int xcount = 0, ocount = 0;

  // Walk down the sequence of board spaces.
  for ( int k = 0; k < RUNLEN; k++ ) {

    // Figure out its row and column index and make sure it's on the board.
    int r = startRow + k * dRow;
    int c = startCol + k * dCol;
    if ( r < 0 || r >= rows || c < 0 || c >= cols )
      return false;

    // Count an X or an O if it's one of those.
    if ( board[ r ][ c ] == 'X' )
      xcount++;
    else if ( board[ r ][ c ] == 'O' )
      ocount++;
  }

  // We have a winner if it's all Xs or Os.
  return xcount == RUNLEN || ocount == RUNLEN;
}
