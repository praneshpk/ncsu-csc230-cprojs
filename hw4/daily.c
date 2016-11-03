/**
  @file daily.c
  @author Pranesh Kamalakanthan (pkamala)

  This program will store, update and report on a daily schedule of activities,
  each with a start time and end time. There will be interactive commands to add
  and remove activities from the schedule and query activities based on different criteria.

*/

#include "schedule.h"

/** 
    Program starting point, will repeatedly prompt user for a command:
    add, remove, schedule, leader, at, match, or quit. Program will terminate
    on quit or end-of-file on standard input.
    
    @return program exit status
*/
int main()
{
  // Creates a new schedule
  Schedule *sched = createSchedule();

  // Sets input buffer for command
  char buffer[15]; 
  int ch;

  // Serves as a stopper for the while loop
  bool quit = false;
  while( !quit ) {
    printf("> ");

    scanf("%14s", buffer);
    if( strcmp(buffer, "add") == 0 ){
      // Frees Activity if parameters are invalid
      Activity *act = readActivity();
      if( !act ) {
        free(act);
        // Flush input and print error
        while ((ch = getchar() != '\n') && (ch != EOF));
        printf("Invalid command\n");
      }
      else {
        if( !addActivity( sched, act ) )
          printf("Schedule conflict\n");
      }
    }
    else if( strcmp(buffer, "remove") == 0){
      if( scanf("%d", &ch) == 1 ){
        if( !removeActivity( sched, ch ) )
          printf("Invalid command\n");
      }
      else{
        // Flush input and print error
        while ((ch = getchar() != '\n') && (ch != EOF));
        printf("Invalid command\n");
      }
    }
    else if( strcmp(buffer, "schedule") == 0 ){
      printf("%s\n",buffer);
    }
    else if( strcmp(buffer, "leader") == 0 ){
      printf("%s\n",buffer);
    }
    else if( strcmp(buffer, "at") == 0 ){
      printf("%s\n",buffer);
    }
    else if( strcmp(buffer, "match") == 0 ){
      printf("%s\n",buffer);
    }
    else if( strcmp(buffer, "quit") == 0 ){
      quit = true;
    }
    else {
      // Flush input and print error
      printf("Invalid command\n");
      while ((ch = getchar() != '\n') && (ch != EOF));
    }
  }
  freeSchedule(sched);
  return 0;
}