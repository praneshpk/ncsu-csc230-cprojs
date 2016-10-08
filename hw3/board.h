/**
  @file board.h
  @author Pranesh Kamalakanthan (pkamala)

  This header file prototypes all of the helper functions
  in board.c for a game of Connect N

*/

#include <stdbool.h>

// This trick will let us define the length of a winning
// run when we compile the program, if we want to.
#ifndef RUNLEN
/** Number of markers in a row required for a win. */
#define RUNLEN 4
#endif

/**
   Return true if there's a winning sequence of markers starting at
   the given board location, startRow, startCol location, either a
   sequence of X characters or O characters.  The dRow and dCol
   parameters indicate what direction to look, with dRow giving
   change-in-row for each step and dCol giving the change-in-column.
   For example, a dRow of -1 and a dCol of 1 would loo for a sequence
   of markers starting from the given start location and diagonally up
   to the right.
   @param rows Number of rows the board has.
   @param cols Number of columns the board has.
   @param board The game board.
   @param startRow Row start position to look for a win.
   @param startCol Column start position to look for a win.
   @param dRow Direction to move vertically looking for a win.
   @param dCol Direction to move horizontally looking for a win.
   @return true if there's a win in the given board location.
 */
bool winner( int rows, int cols, char board[ rows ][ cols ],
             int startRow, int startCol, int dRow, int dCol );
