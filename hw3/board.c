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
      if( winner( 'N', rows, cols, board, i, j, -1, -1, RUNLEN ) ||
          winner( 'N', rows, cols, board, i, j, -1, 1, RUNLEN ) ||
          winner( 'N', rows, cols, board, i, j, 1, 1, RUNLEN ) ||
          winner( 'N', rows, cols, board, i, j, 1, -1, RUNLEN ) ||
          winner( 'N', rows, cols, board, i, j, 0, 1, RUNLEN ) ||
          winner( 'N', rows, cols, board, i, j, 0, -1, RUNLEN ) ||
          winner( 'N', rows, cols, board, i, j, 1, 0, RUNLEN ) ||
          winner( 'N', rows, cols, board, i, j, -1, 0, RUNLEN ) ){
        return 1;
      }
    }
  }

  return 0;
}
bool winner( char player, int rows, int cols, char board[ rows ][ cols ],
             int startRow, int startCol, int dRow, int dCol, int len )
{
  // Number of X and O symbols in this sequence of locations
  int xcount = 0, ocount = 0;

  // Walk down the sequence of board spaces.
  for ( int k = 0; k < len; k++ ) {

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

  // We have a match depending on what players we are looking at.
  if( player == 'X' )
    return xcount == len;
  else if( player == 'O' )
    return ocount == len;
  else
    return xcount == len || ocount == len;

}
void promptMove( char player, int rows, int cols, 
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
  makeMove( player, rows, cols, board, move );
}
bool makeMove( char player, int rows, int cols,
               char board[ rows ][ cols ], int move )
{
  // Makes the available move on the board
  for( int i = rows - 1; i >= 0; i-- ){
    if( board[ i ][ move-1 ] == ' ' ){
      board[ i ][ move-1 ] = player;
      return true;
    }
  }
  return false;
}
void computerMove( int rows, int cols, char board[ rows ][ cols ])
{
  // Checks first to see if the computer can win
  for( int i = 0; i < rows; i++ ){
    for( int j = 0; j < cols; j++ ){
      for( int dr = -1; dr <= 1; dr++ ){
        for( int dc = -1; dc <= 1; dc++ ){
          if( dr == 0 && dc == 0){
            continue;
          }
          if( winner( 'O', rows, cols, board, i, j, dr, dc, 3 ) ){
            // Goes for the win, if possible
            if( makeMove( 'O', rows, cols, board, 3 * dc + (j+1)) ){
              return;
            }
          }
        }
      }
    }
  }
  // Checks to see if the computer can block
  for( int i = 0; i < rows; i++ ){
    for( int j = 0; j < cols; j++ ){
      for( int dr = -1; dr <= 1; dr++ ){
        for( int dc = -1; dc <= 1; dc++ ){
          if( dr == 0 && dc == 0){
            continue;
          }
          if( winner( 'X', rows, cols, board, i, j, dr, dc, 3 ) ){
            // Goes for the block, if possible
            if( makeMove( 'O', rows, cols, board, 3 * dc + (j+1)) ){
              return;
            }
          }
        }
      }
    }
  }
  // Makes best possible move for computer
  for( int i = 0; i < rows; i++ ){
    for( int j = 0; j < cols; j++ ){
      for( int dr = -1; dr <= 1; dr++ ){
        for( int dc = -1; dc <= 1; dc++ ){
          if( dr == 0 && dc == 0){
            continue;
          }
          for( int x = 3; x > 1; x-- ){
            if( winner( 'O', rows, cols, board, i, j, dr, dc, x ) ){
              // Goes for the best possible move
              if( makeMove( 'O', rows, cols, board, x * dc + (j+1)) ){
                return;
              }
            }
          }
        }
      }
    }
  }
  // Otherwise, make move in first available space
  for( int i = 0; i < rows; i++ ){
    for( int j = 0; j < cols; j++ ){
      if( makeMove( 'O', rows, cols, board, j+1 ) ){
        return;
      }
    }
  }
}
