/**
  @file squeeze.c
  @author Pranesh Kamalakanthan (pkamala)

  This component will implement the main function of the squeeze
  program. It will be responsible for handling the command-line arguments,
  reading bytes from the input file, using the codes component to convert them to codes
  and using the bits component to write them out to the output file.
*/

#include "codes.h"
#include "bits.h"

/**
  Program starting point, takes the infile and outfile as command-line
  arguments, and then "squeezes" the infile into the outfile

  @param argc number of command-line arguments
  @param argv list of command-line arguments

  @return program exit status

*/
int main( int argc, char *argv[] )
{
  // Check command-line arguments and read words from file
  if ( argc != 3) {
    fprintf(stderr, "usage: squeeze <infile> <outfile>\n");
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