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
  Print the given board to standard output
  
  @param rows Number of rows the board has
  @param cols Number of columns the board has.
  @param board The game board.
*/
void printBoard( int rows, int cols, char board[ rows ][ cols ] );

/**
  Sets the given board to its initial state, filled with spaces.
  
  @param rows Number of rows the board has
  @param cols Number of columns the board has.
  @param board The game board.
*/
void clearBoard( int rows, int cols, char board[ rows ][ cols ] );

/**
  Checks to see if the game is over by determining if a player
  has won, lost or the board is full

  @param rows Number of rows the board has
  @param cols Number of columns the board has.
  @param board The game board.

  @return 1 if one of the players has one,
          2 if the game board is full but nobody won,
          otherwise return 0.
*/
int gameStatus( int rows, int cols, char board[ rows ][ cols ] );

/**
   Return true if there's a sequence of markers, given by len, starting at
   the given board location, startRow, startCol location, either a
   sequence of X characters or O characters (according to what player
   is passed into the function.  The dRow and dCol parameters indicate
   what direction to look, with dRow giving change-in-row for each step and
   dCol giving the change-in-column.

   @param player 'X' or 'O' that the function is looking for,
          or 'N' for either marker
   @param rows Number of rows the board has.
   @param cols Number of columns the board has.
   @param board The game board.
   @param startRow Row start position to look for a win.
   @param startCol Column start position to look for a win.
   @param dRow Direction to move vertically looking for a win.
   @param dCol Direction to move horizontally looking for a win.
   @param len The length of the Connect N sequence
   @return true if there's a match in the given board location.
 */
bool winner( char player, int rows, int cols, char board[ rows ][ cols ],
             int startRow, int startCol, int dRow, int dCol, int len );

/**
  This function prompts the user for their next move using the given
  player character to indicate which player has the next move (X or O).
  If the column input is valid, the function will make the given move,
  otherwise it will print the required error message and prompt the user
  again for a move. The program will terminate on EOF on standard input

  @param rows Number of rows the board has
  @param cols Number of columns the board has.
  @param board The game board.
*/
void makeMove( char player, int rows, int cols, 
               char board[ rows ][ cols ] );

/**
  This function looks for the best possible move for Player O to either
  win or to prevent the opponenet from winning, if it can.

  @param rows Number of rows the board has
  @param cols Number of columns the board has.
  @param board The game board.
*/
void computerMove( int rows, int cols, char board[ rows ][ cols ]);
