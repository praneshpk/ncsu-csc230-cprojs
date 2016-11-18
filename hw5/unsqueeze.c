/**
  @file unsqueeze.c
  @author Pranesh Kamalakanthan (pkamala)

  This component will implement the main function of the unsqueeze program.
  It will be responsible for handling the command-line arguments, using the bits
  component to read codes from the input file, using the codes component to convert
  them back to characters and writing those to the output file.
*/

#include "bits.h"
#include <stdbool.h>

/**
  Program starting point, takes the infile and outfile as command-line
  arguments, and then "unsqueezes" the infile into the outfile

  @param argc number of command-line arguments
  @param argv list of command-line arguments

  @return program exit status

*/
int main( int argc, char *argv[] )
{
  // Check command-line arguments and read words from file
  if ( argc != 3) {
    fprintf(stderr, "usage: unsqueeze <infile> <outfile>\n");
    exit( 1 );
  }
  else {
    // Opens binary file if it exists
    FILE *input;
    if ( ( input = fopen( argv[1], "rb" ) ) == NULL ) {
      perror( argv[1] );
      exit( EXIT_FAILURE );
    }

    // Opens the given output file for writing
    FILE *output = fopen( argv[2], "w" );

    // Initializes bit buffer for reading
    BitBuffer write = { 0 , 0 };

    // Checks if file matches format code
    int ch; 
    if( ( ch = read5Bits( &write, input)) != 1 ) {
      fprintf(stderr, "Invalid compressed format\n");
      exit( EXIT_FAILURE );
    }

    // Reads each character in the input
    while( true ) {
      if( ( ch = read5Bits( &write, input ) ) == -1 ) {
        break;
      }
      else if( ch == 31 ) {
        if( ( ch = read8Bits( &write, input ) ) == -1 )
          break;
        else
          fputc( ch, output );
      }
      else {
        fputc( codeToSym( ch ), output);
      }
    }
  }
}