/**
  @file codes.h
  @author Pranesh Kamalakanthan (pkamala)

  Header file for the codes.c component, with functions to help 
  map between symbols and the codes used to represent them
*/

#include <stdlib.h>
#include <string.h>

/** Escape code if the code is not found in table of codes */
#define ESCAPE_CODE 31

/** Table of 31 codes used to convert between ASCII and 5-bit code */
static const char CODE[] = "etai\"n solrdc></pm-u.hf_=g:b0y\n";

/**
  Given the ASCII code for a character, this function
  returns the 5-bit code used to represent it.

  @param ch ASCII code
  @return 5-bit code, or escape code 31, if there is
  no code to represent it
*/
int symToCode( unsigned char ch );

/**
  Given a 5-bit code, this function returns the ASCII
  character it represents. This function is only defined for
  codes from 0 up to 30, inclusive.

  @param code 5-bit code
  @return ASCII code for given 5-bit code
*/
int codeToSym( int code );