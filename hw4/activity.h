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
  and return a value the way strcmp does by looking at the startTime of both activities
  
  @param a Activity 1
  @param b Activity 2

  @return negative value if the first activity is earlier
          positive value if the first activity is later
          zero if they are at the same time
*/
int compare( const void *a, const void *b );

/**
  This will free the dynamically allocated memory used to store an activity,
  including the structure itself and the title.

  @param act The given Activity
*/
void freeActivity( Activity *act );