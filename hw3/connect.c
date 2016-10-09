/**
  @file connect.c
  @author Pranesh Kamalakanthan (pkamala)

  This program simulates a game of Connect 4 (or any number, N)
*/

#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


/** 
    Program starting point, asks for board size and begins game by prompting
    the user through standard input until game is over or end-of-file is reached.
    
    @param argc number of command-line arguments, not used.
    @param argv list of command-line arguments, 
            -a automatically chooses good moves for O player

    @return program exit status
*/

int main( int argc, char *argv[] )
{
  // Number of rows and columns of board
  int rows, cols;

  // Player character that will change on each turn,
  // will be changed to X initially in while loop
  char player = 'O';

  // Asks for (n x n) size of the board between 4 and 20 inclusive
  // Exit with status 1 if user inputs invalid pair of integers
  printf( "Rows and cols> ");
  while( scanf( "%d %d", &rows, &cols) != 2 ||
         ( rows < 4 || rows > 20) ||
         ( cols < 4 || cols > 20) ) {

    fprintf( stderr, "Invalid board size\n" );
    exit(1);
  }

  // Create Connect N board
  char board[ rows ][ cols ];

  // Reset board to default
  clearBoard( rows, cols, board );

  // Play game until there is a win or stalemate
  int status;
  while( ( status = gameStatus( rows, cols, board ) ) == 0 ){
    // Switch turns
    if( player == 'X' )
      player = 'O';
    else
      player = 'X';

    printBoard( rows, cols, board );

    // Prompt player for move, or autoplay based on program argument
    if ( player == 'O' &&
         argc == 2 &&
         strcmp( argv[1], "-a" ) == 0 )
      computerMove( rows, cols, board );
    else
      makeMove( player, rows, cols, board );
    
  }
  printBoard( rows, cols, board );

  // Show final game status
  ( status == 1 ) ? printf( "Player %c wins\n", player) :
                    printf( "Stalemate\n" );

  return 0;
}