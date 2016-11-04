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
  char buffer[22]; 
  int ch, h, m;

  // Serves as a stopper for the while loop
  bool quit = false;

  while( !quit ) {
    // Takes user input for a command
    printf("> ");
    if( scanf("%14s", buffer) == EOF ){
      quit = true;
      continue;
    }

    // Add command
    if( strcmp(buffer, "add") == 0 ){
      // Frees Activity if parameters are invalid
      Activity *act = readActivity();
      if( !act ) {
        // Flush input and print error
        while ((ch = getchar() != '\n') && (ch != EOF));
        printf("Invalid command\n");
      }
      else {
        if( !addActivity( sched, act ) ){
          printf("Schedule conflict\n");
        }
      }
    }
    // Remove command
    else if( strcmp(buffer, "remove") == 0){
      if( scanf("%d", &ch) == 1 ){
        if( ! removeActivity( sched, ch ) )
          printf("Invalid command\n");
      }
      else{
        // Flush input and print error
        while ((ch = getchar() != '\n') && (ch != EOF));
        printf("Invalid command\n");
      }
    }
    // Schedule command
    else if( strcmp(buffer, "schedule") == 0 ){
      printSchedule( sched, matchLeader, NULL);
    }
    // Leader command
    else if( strcmp(buffer, "leader") == 0 ){
      scanf("%21s", buffer);
      // Prints schedule with leader filter, if valid
      if( strlen(buffer) > 20 )
        printf("Invalid command\n");
      else
        printSchedule( sched, matchLeader, buffer );
      // Flush input
      while ((ch = getchar() != '\n') && (ch != EOF));
    }
    // At command
    else if( strcmp(buffer, "at") == 0 ){
      // Checks if time is valid
      if( scanf("%d:", &h) != 1 ||
          h < 0 ||
          h > 23 ) {
        printf("Invalid command\n");
      }
      else if( scanf("%d", &m) != 1 ||
          m < 0 ||
          m > 59 ){
        printf("Invalid command\n");
      }
      // Prints schedule with time filter
      else {
        int tm = h * 60 + m;
        printSchedule( sched, matchTime, &tm );
      }
      // Flush input buffer
      while ((ch = getchar() != '\n') && (ch != EOF));

    }
    else if( strcmp(buffer, "match") == 0 ){
      scanf("%21s", buffer);
      if( strlen(buffer) > 20 )
        printf("Invalid command\n");
      else
        printSchedule( sched, matchKeyword, buffer );
      while ((ch = getchar() != '\n') && (ch != EOF));
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