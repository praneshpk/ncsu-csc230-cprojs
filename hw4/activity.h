/**
  @file activity.h
  @author Pranesh Kamalakanthan (pkamala)

  This component will define the Activity struct and functions
  for working directly with activities.

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

/** Initial capacity of the Schedule list */
#define INIT_CAPACITY 10

/**
  Defines the Activity structure (aliased with a typedef) to contain
  fields for the values of all attributes of the activity. The title
  is stored by reference to handle arbitrary lengths.
*/
typedef struct {
  char *title;
  char leader[21];
  int startTime;
  int endTime;
  int id;
} Activity;

/**
  This function will read input from standard input in the same format as
  the arguments to the add command. If valid, it will dynamically allocate
  and initialize an instance of the Activity structure.

  @return pointer to the instance of the Activity struct if valid,
          otherwise return NULL
*/
Activity *readActivity();

/**
  This is a compare function to be used with qsort(). It will take two Activities 
  and return a value the way strcmp does by looking at the startTime of both activities.
  If the start times are the same, it will do a strcmp of the Activity leader
  
  @param a Activity 1
  @param b Activity 2

  @return negative value if the first activity comes before
          positive value if the first activity comes after
*/
int compare( const void *a, const void *b );

/**
  This function will check if the given activity matches the given
  leader string. It will always return true if a NULL is passed into
  lead.

  @param act The given Activity
  @param lead The given leader string
  
  @return true if there is a match or the lead is NULL
          false otherwise
*/
bool matchLeader( Activity *act, void *lead );

/**
  This function will check if the given activity starts at the given
  time or is before the given time and end after the given time.

  @param act The given Activity
  @param tm The given time
  
  @return true if there is a match
          false otherwise
*/
bool matchTime( Activity *act, void *tm );
/**
  This function will check if the keyword exists as a substring in the
  title of the given Activity.

  @param act The given Activity
  @param key The given keyword

  @return true if there is a match
          false otherwise
*/
bool matchKeyword( Activity *act, void *key );

/**
  This will free the dynamically allocated memory used to store an activity,
  including the structure itself and the title.

  @param act The given Activity
*/
void freeActivity( Activity *act );