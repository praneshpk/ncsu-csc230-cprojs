/**
  @file dent.c
  @author Pranesh Kamalakanthan (pkamala)

  This program will read text from standard input and then print out correctly
  indented code based on the nesting of curly brackets

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/** 
    Program starting point, reads and prints out formatted text
    from standard input until end-of-file
    
    @return program exit status, 100 if there are unmatched brackets
*/
int main()
{
  // Initial indentation depth
  int d = 0;
  //bool indent = false;

  for(int ch = getchar(); ch != EOF; ch = getchar()){
    // Discards hard tabs and spaces at beginning of line
    if(ch == ' ' ||
      ch == '\t' ) {
      while( (ch = getchar()) == ' ' ||
              ch == '\t' );
    }

    // Checks for closing bracket at the beginning and decrements depth
    if( ch =='}' ){
      d--;
      // Prints error if there are more } brackets
      if( d < 0 ){
        printf("Unmatched brackets\n");
        return 100;
      }
    }

    // Adds soft tabs for non-empty line
    if( ch !='\n' ) {
      for(int i = 0; i < 2*d; i++)
        putchar(' ');
    }

    // Checks for opening bracket and increments depth
    if( ch == '{' )
      d++;

    // Print first character
    putchar(ch);

    // Add soft tabs for next character
    if( ch =='\n' ) {
      for(int i = 0; i < 2*d; i++)
        putchar(' ');
    }

    // Read rest of line and increment or decrement depth based on bracket
    for(ch = getchar(); ch != '\n'; ch = getchar()){
      if( ch == '{' )
        d++;
      else if( ch == '}' ){
        d--;
        if( d < 0 ){
          printf("Unmatched brackets\n");
          return 100;
        }
      }
      putchar(ch);
    }
    // Print last character
    putchar(ch);
  }

  // Prints error if there are more { brackets
  if( d > 0){
    printf("Unmatched brackets\n");
    return 100;
  }
  return 0;
}