#include "codes.h"

int symToCode( unsigned char ch )
{
  for( int i = 0; i < strlen(CODE); i++ )
    if( CODE[i] == ch )
      return i;
  return ESCAPE_CODE;
}

int codeToSym( int code )
{
  return CODE[ code ];
}