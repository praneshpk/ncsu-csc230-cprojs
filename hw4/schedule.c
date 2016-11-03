#include "schedule.h"

Schedule *createSchedule()
{
  // Allocates data for the Schedule structure
  Schedule *sched = (Schedule *)malloc( sizeof( Schedule ) );

  // Sets the initial memory capacity of the Schedule list
  sched->capacity = INIT_CAPACITY;

  // Sets the initial size of the Schedule list
  sched->size = 0;

  // Sets the initial NextID for an activity
  sched->nextID = 1;

  // Allocates data for the list array in Schedule
  sched->list = (Activity ** )malloc( sched->capacity * sizeof( Activity * ) );

  return sched;
}
void freeSchedule( Schedule *sched )
{
  // Frees each element in Schedule List
  for( int i = 0; i < sched->size; i++ )
    freeActivity( sched->list[i] );
  
  // Frees the list array and Schedule
  free(sched->list);
  free(sched);
}

bool addActivity( Schedule *sched, Activity *act )
{
  // Runs through the list of activities
  for( int i = 0; i < sched->size; i++ ){
    // Checks if there is the same leader
    if( strcmp(act->leader, sched->list[i]->leader) == 0){
      // Frees activity if there is an overlap
      if(  act->startTime == sched->list[i]->startTime ||
          ( act->startTime > sched->list[i]->startTime &&
            act->startTime < sched->list[i]->endTime ) || 
          ( act->endTime > sched->list[i]->startTime &&
            act->endTime < sched->list[i]->endTime ) ) {
        freeActivity(act);
        return false;
      }
    }
  }
  // Resizes list if needed
  if( sched->size >= sched->capacity ){
    sched->capacity *= 2;
    sched->list = realloc( sched->list, sched->capacity * sizeof( Activity * ) );
  }
  // Sets ID for Activity and increments next ID
  act->id = (sched->nextID)++;
  
  // Adds activity to schedule and increments schedule size
  sched->list[(sched->size)++] = act;

  return true;
}
bool removeActivity( Schedule *sched, int id )
{
  // Runs through the list of activities
  for( int i = 0; i < sched->size; i++ ){
    // Remove activity if ID matches
    if( sched->list[i]->id == id ){
      
      // Allocating memory for a temporary list with one less element
      Activity **temp = ( Activity ** )malloc( ( sched->size - 1 ) * sizeof( Activity * ) );
     
      // Copies every element before the Activity, if it's not the first element
      if( i != 0)
        memcpy(temp, sched->list,  i  * sizeof( Activity * ) );
      // Copies every element after the Activity, if it's not the last element
      if( i != (sched->size - 1 ) )
        memcpy(temp+i, sched->list + i + 1, ( sched->size - i -1 ) * sizeof( Activity * ));
      
      // Frees the Activity and Schedule list
      freeActivity( sched->list[i] );  
      free( sched->list );

      // Copies the temporary list to the new list
      sched->list = temp;
      sched->size --;
      
      return true;
    }
  }
  return false;
}
void printSchedule( Schedule *sched, bool (*test)(Activity *, void *arg), void *arg )
{
  putchar('\n');
  qsort( sched->list, sched->size, sizeof( Activity * ), compare );

  for( int i = 0; i < sched->size; i++ ){
    if( ( *test )( sched->list[i], arg ) ){
      printf("%2d:%02d %2d:%02d (%03d) %s %s\n", sched->list[i]->startTime / 60, sched->list[i]->startTime % 60,
            sched->list[i]->endTime / 60, sched->list[i]->endTime % 60, sched->list[i]->id,
            sched->list[i]->leader, sched->list[i]->title );
    }
  }
}