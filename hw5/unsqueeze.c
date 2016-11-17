/**
  @file unsqueeze.c
  @author Pranesh Kamalakanthan (pkamala)

  This component will implement the main function of the unsqueeze program.
  It will be responsible for handling the command-line arguments, using the bits
  component to read codes from the input file, using the codes component to convert
  them back to characters and writing those to the output file.
*/

#include "codes.h"
#include "bits.h"
#include <stdio.h>

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
    // Opens file if it exists
    FILE *fp;
    if ( ( fp = fopen( argv[1], "r" ) ) == NULL ) {
      perror( argv[1] );
      exit( EXIT_FAILURE );
    }
    fclose(fp);
    return 0;
  }
}