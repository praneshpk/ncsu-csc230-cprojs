#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void printBoard( int rows, int cols, char board[ rows ][ cols ] )
{
  printf("\n");
  for( int i = 0; i < rows; i++ ){
    
    // Prints board spaces
    printf( "|" );
    for( int j = 0; j < cols; j++ )
      printf( "%c|", board[i][j] );

    // Prints bottom separator and numbers
    if( i == rows - 1){
      printf( "\n" );
      for( int j = 0; j <= cols * 2; j++ ){
        if( j % 2 == 0 )
          printf("+");
        else
          printf("-");
      }
      printf("\n");
      for( int j = 0; j < cols; j++ )
        printf( " %d", (j + 1) % 10 );
    }
    printf( "\n" );
  }
}
void clearBoard( int rows, int cols, char board[ rows ][ cols ] )
{
  for( int i = 0; i < rows; i++ ){
    for( int j = 0; j < cols; j++ )
      board[i][j] = ' ';
  }
}
int gameStatus( int rows, int cols, char board[ rows ][ cols ] )
{
  // Checks if board is full
  for( int i = 0; i < cols; i++ ){
    if( board[ 0 ][ i ] == ' ')
      break;
    else if( i == cols - 1 )
      return 2;
  }

  // Checks if there is a winner in all directions
  for( int i = 0; i < rows; i++ ){
    for( int j = 0; j < cols; j++ ){ 
      if( winner( rows, cols, board, i, j, -1, -1 ) ||
          winner( rows, cols, board, i, j, -1, 1 ) ||
          winner( rows, cols, board, i, j, 1, 1 ) ||
          winner( rows, cols, board, i, j, 1, -1 ) ||
          winner( rows, cols, board, i, j, 0, 1 ) ||
          winner( rows, cols, board, i, j, 0, -1 ) ||
          winner( rows, cols, board, i, j, 1, 0 ) ||
          winner( rows, cols, board, i, j, -1, 0 ) ){
        return 1;
      }
    }
  }

  return 0;
}
bool winner( int rows, int cols, char board[ rows ][ cols ],
             int startRow, int startCol, int dRow, int dCol )
{
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
void makeMove( char player, int rows, int cols, 
               char board[ rows ][ cols ] )
{
  // Prompts user for a valid move
  int move;
  char eof;
  printf( "%c move> ", player );
  while( ( eof = scanf( "%d", &move ) ) != 1 ||
         ( move-1 < 0 || move-1 >= cols ) ||
         board[ 0 ][ move-1 ] != ' '){
    
    // Terminate program at EOF
    if( eof == EOF )
      exit(0);

    // Flush standard input
    while((eof = fgetc(stdin)) != '\n');
    printf( "Invalid move\n%c move> ", player );
  }

  // Make move on available spot
  for( int i = rows - 1; i >= 0; i-- ){
    if( board[ i ][ move-1 ] == ' ' ){
      board[ i ][ move-1 ] = player;
      break;
    }
  }
}
void computerMove( int rows, int cols, char board[ rows ][ cols ])
{
  
}
