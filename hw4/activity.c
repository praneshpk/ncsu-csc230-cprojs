#include "activity.h"

Activity *readActivity()
{
  char buffer[22], ch;
  int h, m, start, end;

  // Checks if start time is valid
  if( scanf("%d:", &h) != 1 ||
      h < 0 ||
      h > 23 ) {
    return NULL;
  }
  if( scanf("%d", &m) != 1 ||
      m < 0 ||
      m > 59 ){
    return NULL;
  }
  
  // Sets the start time variable in minutes
  start = h * 60 + m;

  // Checks if end time is valid
  if( scanf("%d:", &h) != 1 ||
      h < 0 ||
      h > 23 ) {
    return NULL;
  }
  if( scanf("%d", &m) != 1 ||
      m < 0 ||
      m > 59 ){
    return NULL;
  }

  // Sets the end time variable in minutes
  end = h * 60 + m;

  // Checks if the range between the times are valid
  if( end - start <= 0 )
    return NULL;

  // Flush newline character
  getchar();

  // Checks if the leader string is a valid length
  for(int i=0; i<22; i++ ){
    if( ( ch = getchar()) == '\n' ||
          ch == ' ' ||
          i == 21  ){
      buffer[ i+1 ] = '\0';
      break;
    }
    else{
      buffer[i] = ch;
    }
  }
  if( strlen(buffer) > 20 ){
    return NULL;
  }

  // Allocates data for the Activity structure and title string
  int i = 0;
  int cap = INIT_CAPACITY;

  Activity *act = (Activity *)malloc( sizeof( Activity ) );
  //memset(act, '\0', sizeof( Activity ));
  act->title = (char *)malloc( cap * sizeof( char ) );
  //memset(act->title, '\0', cap * sizeof( char ));

  // Writes to title
  while( ( ch = getchar()) !='\n' ){
    act->title[ i++ ] = ch;

    // Reallocates data if necessary
    if( i >= cap ){
      cap *= 2;
      act->title = realloc( act->title, cap * sizeof( char ));
    }
  }
  act->title[ i ] = '\0';
  printf( "%s\n", act->title);

  // Sets fields in activity
  act->startTime = start;
  act->endTime = end;
  memcpy(act->leader, buffer, 21 );
  
  return act;
}
void freeActivity( Activity *act )
{
  free(act->title);
  printf("act->title freed\n\n");
  free(act);
  printf("act freed\n\n");
}