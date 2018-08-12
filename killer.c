/*
 * killer.c
 *
 *  Created on: Jul 26, 2018
 *      Author: Xinmeng Zhang
 */

#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/** indicates process is running */
bool stop = false;

/** own process ID*/
pid_t pid;

/** process ID of another process */
static pid_t otherPID;


/** The SIGTSTP handler pauses the program*/
void SIGTSTP_handler(int sig) {
	printf("Received SIGTSTP: suspending\n");
	pause();
}

/** The SIGCONT handler redisplays the choices*/
void SIGCONT_handler(int sig) {
	printf("\t\tMenu\n");
	printf("1 == SIGTSTP\n");
	printf("2 == SIGCONT\n");
	printf("3 == SIGTERM\n");
	printf("4 == SIGUSR1\n");
	printf("5 == SIGUSR2\n");
}

/** The SIGTERM handler terminates the program with exit status EXIT_SUCCESS*/
void SIGTERM_handler(int sig) {
	stop = true;
	printf("Received SIGTERM: terminating normally\n");
}

/** The SIGUSR1 handler prints the current process ID*/
void SIGUSR1_handler(int sig) {
	printf("Current process ID: %d\n", pid);
}

/** The SIGUSR1 handler prints the other process ID*/
void SIGUSR2_handler(int sig) {
	printf("Other process ID: %d\n", otherPID);
}

/** The helper function to handle if the program recieves an erro return
* status -1 from the kill() function
*/
void error() {
	printf("Process %d no longer available\n", otherPID);
	kill(pid, SIGTERM);
}


int main() {
   // Register signal and signal handler
   signal(SIGTSTP, SIGTSTP_handler);
   signal(SIGCONT, SIGCONT_handler);
   signal(SIGTERM, SIGTERM_handler);
   signal(SIGUSR1, SIGUSR1_handler);
   signal(SIGUSR2, SIGUSR2_handler);

   // The process id
   pid = getpid();
   printf("My process id is: %d\n", pid);
   printf("Please enter the pid of other program:\n");
   // input other process id
   scanf("%d", &otherPID);
   // first display menu
   if (kill(otherPID, SIGCONT) == -1) {
   	    error();
		return EXIT_FAILURE;
	}

   int choice;
   while(! stop) {
	   // keep asking for choice
	   printf("Please enter your choice:\n");
	   scanf("%d", &choice);
	   if (choice == 0) {
		   break;
	   }
	   else if (choice == 1) {
		   if (kill(otherPID, SIGTSTP) == -1) {
			   error();
			   return EXIT_FAILURE;
		   }
	   }
	   else if (choice == 2) {
    	  if (kill(otherPID, SIGCONT) == -1) {
    	  	   error();
    	  	   return EXIT_FAILURE;
    	  }
	   }
	   else if (choice == 3) {
		   if (kill(otherPID, SIGTERM) == -1) {
			   error();
			   return EXIT_FAILURE;
		   }
	   }
	   else if (choice == 4) {
		   if (kill(otherPID, SIGUSR1) == -1) {
			   error();
			   return EXIT_FAILURE;
		   }
	   }
	   else if (choice == 5) {
		   if (kill(otherPID, SIGUSR2) == -1) {
			   error();
			   return EXIT_FAILURE;
		   }
	   }
	   else {
		   printf("Invalid choice\n");
		}
   }
   return EXIT_SUCCESS;
}


