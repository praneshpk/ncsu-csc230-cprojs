#include "bits.h"

void write5Bits( int code, BitBuffer *buffer, FILE *fp )
{
  //printf("writing (%d)\n",code);
  int op;
  // Run loop for 5 bits
  for( int i = 16; i > 0; i/=2 ) {
    //if( buffer->bcount < BITS_PER_BYTE - 5 )
      //op = ( code & i ) << ( BITS_PER_BYTE - ( buffer->bcount + (int)log2(i) + 1 ) );
      op = ( ( code & i ) >> (int) log2(i) ) << ( BITS_PER_BYTE - buffer->bcount - 1 );
    buffer->bits |= op;
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
    // Add one high-order bit to the buffer 
    if( buffer->bcount < BITS_PER_BYTE - 8 )
      buffer->bits |= ( code & i ) << buffer->bcount;
    else
      buffer->bits |= ( code & i ) >> ( BITS_PER_BYTE - buffer->bcount );
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