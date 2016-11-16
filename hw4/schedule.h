/**
  @file schedule.h
  @author Pranesh Kamalakanthan (pkamala)

  This component will define the Schedule struct and functions
  for working with schedules.
*/

#include "activity.h"

/**
  Defines the Schedule structure (aliased with a typedef) to be used as a container for a resizable
  array of pointers to activities. The nextID variable is uesed to keep track of what ID will
  be assigned to the next activity added to Schedule. The capacity keeps track of the memory capacity of
  the Schedule list, while the size keeps track of how many items are in the Schedule list.
*/
typedef struct {
  int capacity;
  int size;
  Activity **list;
  int nextID;
} Schedule;

/**
  This will dynamically allocate space for a new, empty Schedule instance.
  This will include creating the reziable array of activity pointers
  stored within the Schedule
  
  @return pointer to the new Schedule instance

*/
Schedule *createSchedule();

/**
  This will free all the dynamically allocated memory used by a schedule,
  including the schedule object itself, its resizable array of Activity
  pointers, and the Activity instances themselves

  @param sched The given Schedule
*/
void freeSchedule( Schedule *sched );

/**
  This will add the given activity to the given schedule, growing the
  resizable array as needed. This function is responsible for checking /
  scheduling conflicts
  
  @param sched The given Schedule
  @param act The given Activity

  @return true if successful, false if the given activity overlaps with
  an activity the leader is already doing.
*/
bool addActivity( Schedule *sched, Activity *act );

/**
  This function will remove the activity defined by the given ID and
  free it from memory

  @param sched The given Schedule
  @param id The given Activity ID
  
  @return true if successful, false if the id doesn't exist
*/
bool removeActivity( Schedule *sched, int id );

/**
  This goes through the list of activities and prints them in the right
  order. The program runs the test function to make sure it should print
  the activity or not.

  @param sched The given Schedule
  @param test The test function 
  @param arg Additional arguments given for the function
*/
void printSchedule( Schedule *sched, bool (*test)(Activity *, void *arg), void *arg );