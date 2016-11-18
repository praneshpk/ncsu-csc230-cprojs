#include "bits.h"

void write5Bits( int code, BitBuffer *buffer, FILE *fp )
{
  // Run loop for 5 bits
  for( int i = 16; i > 0; i/=2 ) {
    // Perform bit push operation
    buffer->bits |= ( ( code & i ) >> (int) log2(i) ) << ( BITS_PER_BYTE - buffer->bcount - 1 );
    buffer->bcount++;
    
    // Flush buffer if it's full
    if( buffer->bcount == 8 )
      flushBits( buffer, fp );
  }
}

void write8Bits( int code, BitBuffer *buffer, FILE *fp )
{
  // Run loop for 8 bits
  for( int i = 128; i > 0; i/=2 ) {
    // Perform bit push operation
    buffer->bits |= ( ( code & i ) >> (int) log2(i) ) << ( BITS_PER_BYTE - buffer->bcount - 1 );
    buffer->bcount++;
    
    // Flush buffer if it's full
    if( buffer->bcount == 8 )
      flushBits( buffer, fp );
  }
}

void flushBits( BitBuffer *buffer, FILE *fp )
{
  fputc( buffer->bits, fp);
  buffer->bits = 0;
  buffer->bcount = 0;
}

int read5Bits( BitBuffer *buffer, FILE *fp )
{
  int res = 0;
  int ch = fgetc(fp);
  if( ch == EOF ) {
    if( buffer->bcount == 0 )
      return -1;
    else {
      res = buffer->bits >> ( BITS_PER_BYTE - 5 );
      buffer->bcount = 0;
      fseek(fp, 0, SEEK_END);
      return res;
    }
  }
  else if( buffer->bcount == 5 ) {
    res = buffer->bits >> ( BITS_PER_BYTE - 5 );
    buffer->bits = 0;
    buffer->bcount = 0;
    fseek( fp, -1, SEEK_CUR );
  }
  else if( buffer->bcount == 8 ) {
    res = buffer->bits >> ( BITS_PER_BYTE - 5 );
    buffer->bits = buffer->bits << 5;
    buffer->bcount = buffer->bcount - 5 + chpos;
    buffer->bits |= (ch & ( (int) pow( 2, chpos ) - 1 ) ) << ( 5 - chpos );
  }
  else if( buffer->bcount == 0 ) {
    res = ch >> ( BITS_PER_BYTE - 5 );
    buffer->bits = ch << 5 ;
    buffer->bcount = BITS_PER_BYTE - 5;
  }
  else if( buffer->bcount > 5 ){
    res = buffer->bits >> ( BITS_PER_BYTE - 5 );
    buffer->bits = buffer->bits << 5;
    chpos = buffer->bcount - 5;
    buffer->bits |= ch >> chpos;
    buffer->bcount = 8;
    fseek( fp, -1, SEEK_CUR );
  }
  else {
    buffer->bits |= ( ch >> buffer->bcount );
    res = buffer->bits >> ( BITS_PER_BYTE - 5 );
    int size = buffer->bcount;
    buffer->bits = buffer->bits << 5;
    buffer->bcount = BITS_PER_BYTE - 5;
    buffer->bits |= ( ch & ( (int) pow( 2, size ) - 1 ) ) << ( BITS_PER_BYTE - buffer->bcount - size);
    buffer->bcount += size;
  }
  return res;
}

int read8Bits( BitBuffer *buffer, FILE *fp )
{
  int ch;
  int res = buffer->bits;
  if( ( ch = fgetc(fp) ) == EOF )
    return -1;
  buffer->bits = ch;
  return res;
}