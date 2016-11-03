#include "schedule.h"

Schedule *createSchedule()
{
  // Allocates data for the Schedule structure
  Schedule *sched = (Schedule *)malloc( sizeof( Schedule ) );

  // Sets the initial memory capacity of the Schedule list
  sched->capacity = INIT_CAPACITY;

  // Sets the initial size of the Schedule list
  sched->size = -1;

  // Sets the initial NextID for an activity
  sched->nextID = 0;

  // Allocates data for the list array in Schedule
  sched->list = (Activity *)malloc( sched->capacity * sizeof( Activity ) );

  return sched;
}
void freeSchedule( Schedule *sched )
{
  //sched->list = NULL;
  printf("size %d\n",sched->size);
  for( int i = 0; i < sched->size; i++ ){
    freeActivity( &sched->list[i] );
    printf("freed activity %d\n\n",i);
  }
  //free(sched->list);
  printf("freed list\n");
  free(sched);
}

bool addActivity( Schedule *sched, Activity *act )
{
  // Runs through the list of activities
  for( int i = 0; i < sched->size; i++ ){
    // Checks if there is the same leader
    if( strcmp(act->leader, sched->list[i].leader) == 0){
      // Frees activity if there is an overlap
      if(  act->startTime == sched->list[i].startTime ||
          ( act->startTime > sched->list[i].startTime &&
            act->startTime < sched->list[i].endTime ) || 
          ( act->endTime > sched->list[i].startTime &&
            act->endTime < sched->list[i].endTime ) ) {
        freeActivity(act);
        return false;
      }
    }
  }
  // Resizes list if needed
  if( sched->size >= sched->capacity ){
    sched->capacity *= 2;
    sched->list = realloc( sched->list, sched->capacity * sizeof( Activity ) );
  }
  // Sets ID for Activity and increments next ID
  act->id = (sched->nextID)++;
  // Adds activity to schedule
  sched->list[++(sched->size)] = *act;
  // Increments schedule size
  //(sched->size)++;
  printf("act id: %d, nextid: %d\n",act->id, sched->nextID);
  return true;
}
bool removeActivity( Schedule *sched, int id )
{
  Activity *list = sched->list;
  // Runs through the list of activities
  //for( int i = 0; i < sched->size; i++ ){
  while(sched->list){
    // Remove activity if ID matches
    if( sched->list->id == id ){
      printf("%d freed \n",sched->list->id);
      freeActivity( sched->list++ );
      sched->list = list;
      //(sched->size)--;
      return true;
    }
  }
  return false;
}