#include "document.h"

Line *loadLine( FILE *fp )
{
  // Dynamically allocate a Line structure
  Line *line = (Line *)malloc( sizeof( Line ) );

  // Read one line and store it in text of Line structure
  if( !fgets( line->text, line->len = strlen(line->text), fp ) ) {
    freeLine( line );
    return NULL;
  }

  // Set capacity of Line structure
  line->cap = line->len + 1;

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
  Document *doc = (Document *)malloc( sizeof( Document ) );
  
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
  while( (read = loadLine( fp )) ) {
    doc->lines[ doc->len ] = read;
    doc->len ++;
    // Reallocates memory if lines array reaches max capacity
    if( doc->len >= doc->cap) {
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
  for( int i = 0; i < doc->len; i++ ) {
    fputs( doc->lines[i]->text, fp );
    fputc( '\n', fp );
  }

  return true;
}

bool moveCursor( Document *doc, CursorDir dir )
{
  switch(dir) {
    case CursorUp:
      if( doc->cCol - 1 >= 0 ) {
        doc->cCol --;
        return true;
      }
      break;
    case CursorRight:
      if( doc->cRow + 1 < doc->lines[doc->cCol]->len + 1) {
        doc->cRow ++;
        return true;
      }
      break;
    case CursorDown:
      if( doc->cCol + 1 < doc->len + 1 ) {
        doc->cCol ++;
        return true;
      }
      break;
    case CursorLeft:
      if( doc->cRow - 1 >= 0 ) {
          doc->cRow --;
          return true;
        }
      break;
  }
  return false;
}

void freeDocument( Document *doc )
{
  for( int i = 0; i < doc->len; i++ )
    freeLine( doc->lines[i] );
  free( doc->lines );
  free( doc );
}