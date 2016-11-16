#include "activity.h"

Activity *readActivity()
{
  char buffer[22], ch;
  int h, m, start, end;

  // Checks if start time is valid
  if ( scanf("%d", &h) != 1 ||
      h < 0 ||
      h > 23 ) {
    return NULL;
  }
  // Removes spaces around :
  if ( getchar() != ':'){
    if ( getchar() !=':')
      return NULL;
    getchar();
  }
  if ( scanf("%d", &m) != 1 ||
      m < 0 ||
      m > 59 ){
    return NULL;
  }

  // Sets the start time variable in minutes
  start = h * 60 + m;

  // Checks if end time is valid
  if ( scanf("%d", &h) != 1 ||
      h < 0 ||
      h > 23 ) {
    return NULL;
  }
  // Removes spaces around :
  if ( getchar() != ':'){
    if ( getchar() !=':')
      return NULL;
    getchar();
  }
  if ( scanf("%d", &m) != 1 ||
      m < 0 ||
      m > 59 ){
    return NULL;
  }

  // Sets the end time variable in minutes
  end = h * 60 + m;

  // Checks if the range between the times are valid
  if ( end - start <= 0 )
    return NULL;

  // Flush newline character
  getchar();

  // Checks if the leader string is a valid length
  for (int i=0; i<22; i++ ){
    if ( ( ch = getchar()) == '\n' ||
          ch == ' ' ||
          i == 21  ){
      // Adds NULL terminator
      buffer[ i ] = '\0';
      break;
    }
    else{
      buffer[i] = ch;
    }
  }
  if ( strlen(buffer) > 20 ){
    return NULL;
  }

  // Allocates data for the Activity structure and title string
  int i = 0;
  int cap = INIT_CAPACITY;

  Activity *act = (Activity *)malloc( sizeof( Activity ) );
  act->title = (char *)malloc( cap * sizeof( char ) );

  // Writes to title
  while( ( ch = getchar()) !='\n' ){
    act->title[ i++ ] = ch;
    // Reallocates data if necessary
    if ( i >= cap ){
      cap *= 2;
      act->title = realloc( act->title, cap * sizeof( char ));
    }
  }
  act->title[ i ] = '\0';

  // Sets fields in activity
  act->startTime = start;
  act->endTime = end;
  memcpy(act->leader, buffer, 21 );
  
  return act;
}
int compare( const void *a, const void *b )
{
  // Computes difference in start times
  int res = (*(Activity **) a)->startTime - (*(Activity **)b)->startTime;
  // Computes difference in if start time is the same
  if ( res == 0 ){
    return strcmp( (*(Activity **) a)->leader, (*(Activity **) b)->leader );
  }
  else
    return res;
}
bool matchLeader( Activity *act, void *lead )
{
  if ( lead == NULL )
    return true;
  else if ( strcmp( act->leader, (char *) lead ) == 0)
    return true;
  else
    return false;
}
bool matchTime( Activity *act, void *tm )
{
  if ( ( act->startTime == *(int *)tm ||
        act->startTime < *(int *)tm ) &&
        act->endTime > *(int *)tm )
    return true;
  else
    return false;
}
bool matchKeyword( Activity *act, void *key )
{
  if ( strcasestr( act->title, key ) )
    return true;
  else
    return false;
}
void freeActivity( Activity *act )
{
  // Frees title string in act
  free(act->title);
  // Frees activity
  free(act);
}