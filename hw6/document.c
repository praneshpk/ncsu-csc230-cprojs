#include "document.h"

Line *loadLine( FILE *fp )
{
  // Dynamically allocate a Line structure
  Line *line = (Line *)malloc( sizeof( Line ) );
  line->cap = INIT_CAP;
  line->len = 0;
  line->text = (char *)malloc( line->cap );

  // Checks if line contains any data
  char ch;
  if ( ( ch = fgetc( fp )) == EOF) {
    freeLine( line );
    return NULL;
  }
  if ( ch == '\n' ) {
    line->text[0] = '\0';
    return line;
  }
  // Updates line, character by character, reallocating if necessary
  do {
    line->text[ line->len ++ ] = ch;
    if ( line->len >= line->cap ) {
      line->cap *= 2;
      line->text = ( char * )realloc( line->text, line->cap );
    }
    line->text[ line->len + 1 ] = '\0';
  } while ( ( ch = fgetc( fp )) != '\n' && ch != EOF);
  return line;
}

void freeLine( Line *line )
{
  // Frees the text in the Line structure
  free( line->text );
  // Frees the Line structure
  free( line );
}

Document *loadDocument( const char *filename )
{
  // Dynamically allocate a Document structure
  Document *doc = ( Document * )malloc( sizeof( Document ) );
  
  // Initialize Document variables
  doc->cap = INIT_CAP;
  doc->len = 0;
  doc->cRow = 0;
  doc->cCol = 0;

  // Dynamically allocate the lines array
  doc->lines = ( Line ** )malloc( doc->cap * sizeof( Line * ) );

  // Opens given file for reading
  FILE *fp = fopen( filename, "r" );

  // Declare pointer to the line read
  Line *read;

  // Adds lines to array until EOF
  while ( (read = loadLine( fp )) ) {
    doc->lines[ doc->len ++ ] = read;
    // Reallocates memory if lines array reaches max capacity
    if ( doc->len >= doc->cap) {
      doc->cap *= 2;
      doc->lines = ( Line ** )realloc( doc->lines, doc->cap );
    }
  }
  // Closes file
  fclose( fp );

  return doc;
}

bool saveDocument( Document *doc, const char *filename )
{
  // Opens given file for writing
  FILE *fp = fopen( filename, "w" );

  // Writes each line to file
  for ( int i = 0; i < doc->len; i++ ) {
    fputs( doc->lines[i]->text, fp );
    fputc( '\n', fp );
  }
  fclose(fp);

  return true;
}

bool moveCursor( Document *doc, CursorDir dir )
{
  switch(dir) {
    case CursorUp:
      if ( doc->cRow - 1 >= 0 ) {
        doc->cRow --;
        if ( doc->cCol > doc->lines[doc->cRow]->len  )
          doc->cCol = doc->lines[doc->cRow]->len;
        return true;
      }
      break;
    case CursorRight:
      if ( doc->cCol + 1 <= doc->lines[doc->cRow]->len ) {
        doc->cCol ++;
        return true;
      }
      break;
    case CursorDown:
      if ( doc->cRow + 1 < doc->len ) {
        doc->cRow ++;
        if ( doc->cCol > doc->lines[doc->cRow]->len  )
          doc->cCol = doc->lines[doc->cRow]->len;
        return true;
      }
      break;
    case CursorLeft:
      if ( doc->cCol - 1 >= 0 ) {
          doc->cCol --;
          return true;
        }
      break;
  }
  return false;
}

void freeDocument( Document *doc )
{
  for ( int i = 0; i < doc->len; i++ )
    freeLine( doc->lines[i] );
  free( doc->lines );
  free( doc );
}