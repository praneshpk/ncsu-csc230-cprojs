/**
  @file cross.c
  @author Pranesh Kamalakanthan (pkamala)

  This program is a crossword helper:
  it reads a list of dictionary words and then generates possible answers
  that match characters that the user has already figured out.

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/** Limits for word list */
#define WORD_LIMIT 100000
#define LETTER_LIMIT 20

/** Storage of the word list */
static char words[WORD_LIMIT][LETTER_LIMIT];

/** Number of words in word list */
int wordCount = 0;

/**
  This function will read the word list from a given file and store it in the
  global words array and set wordCount appropriately

  @param filename the file with the given name that contains the word list

*/
void readWords( char const *filename )
{

  // Opens file if it exists
  FILE *fp;
  if ( ( fp = fopen( filename, "r" ) ) == NULL ) {
    fprintf(stderr, "Can't open word file\n");
    exit( EXIT_FAILURE );
  }
  
  // Keeps count of the letter count in a word
  int letterCount = 0;
  
  // Reads all file input characters
  for( char ch = fgetc(fp); ch != EOF; ch = fgetc(fp) ){
    
    // Updates letter / word count, word list and  
    // checks if there are any non-lowercase letters
    if( ch == ' ' ||
        ch == '\n'){
      letterCount = 0;
      wordCount++;
    }
    else if( ch < 'a' || 
        ch > 'z' ){
      fprintf(stderr, "Invalid word file\n");
      exit( EXIT_FAILURE );
    }
    else {
      words[ wordCount ][ ++letterCount - 1 ] = ch;
    }

    // Checks if file contents meet requirements
    if( letterCount > LETTER_LIMIT ||
        wordCount > WORD_LIMIT){
      fprintf(stderr, "Invalid word file\n");
      exit( EXIT_FAILURE );
    }
  }
  
}

/**
  Prompts the user for a pattern and stores it in a given array pat

  @param pat string to store pattern

  @return true if the pattern is valid, false otherwise.
*/ 
bool getPattern( char *pat )
{
  // Keeps count of pattern characters
  int count = 0;
  printf("pattern> ");

  // Reads and validates pattern by each character
  for( char ch = getchar(); ch != '\n'; ch = getchar() ){
    if(ch == EOF){
      exit(0);
    }
    else if( count++ <= LETTER_LIMIT &&
        ( ch == '?' ||
        ( ch >= 'a' && 
        ch <= 'z' ) ) ){
      *pat++ = ch;
    }
    else {
      printf("Invalid pattern\n");
      strcpy(pat, "");
      return false;
    }
  }
  strcpy(pat,"");
  return true;
}

/**
  Given a word and a pattern, this function
  checks if the word matches the pattern
  
  @param word given word
  @param pat given pattern

  @return true if the given word matches the pattern, false otherwise.
*/
bool matches( char const *word, char const *pat )
{
  // Checks if string lengths are equal
  if( strlen(word) == strlen(pat) ){
    
    // Checks if the word and pattern is the same
    if( strcmp(word, pat) == 0 ){
      return true;
    }

    // Runs through each character in the word to see if it matches the pattern
    for(int i=0; i < strlen(pat); i++){
      if(word[i] != pat[i] &&
        pat[i] != '?'){
        return false;
      }
    }
    return true;
  }
  else{
    return false;
  }
}

/**
  Program starting point, takes the name of a file containing the word list as a
  command-line argument, and then will repeatedly prompt the user for a pattern
  until it reaches EOF on standard input

  @param argc number of command-line arguments
  @param argv list of command-line arguments

  @return program exit status

*/
int main( int argc, char *argv[] )
{
  
  // Check command-line arguments and read words from file
  if ( argc != 2){
    fprintf(stderr, "usage: cross <word-file>\n");
    exit( EXIT_FAILURE );
  }
  else{
    readWords( argv[1] );
  }

  // Prompts user for a valid pattern
  char pattern[LETTER_LIMIT];
  while( true ){
    while( !getPattern( pattern ) );

    // Prints all words that match pattern
    for( int i=0; i < WORD_LIMIT; i++ ){
      if( matches( words[i], pattern ) ){
        printf( "%s\n", words[i] );
      }
    }

    // Resets pattern
    strcpy(pattern, "");
  }

  return 0;
}