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

/** own process ID*/
pid_t pid;

/** process ID of another process */
static pid_t otherPID;

/**
 * Handle SIGTSTP as request to stop/suspend process. Similar to
 * SIGSTOP, but enables application to intercept and handle the
 * signal.  Typing CNTL-Z into a terminal sends SIGTSTP to the
 * process associated with the keyboard.
 */
void SIGTSTP_handler(int sig) {
	printf("Received SIGTSTP: suspending\n");
	pause();
}

/**
 * Handle SIGCONT as notification that the process is continuing.
 * And re-display the choices.
 */
void SIGCONT_handler(int sig) {
	printf("Received SIGCONT: resuming\n");
	display();
}

/**
 * Handle SIGTERM as request to terminate the process normally.
 * Similar to SIGKILL but enables application to intercept and
 * handle the signal.  This handler exit the process immediately.
 */
void SIGTERM_handler(int sig) {
	printf("Received SIGTERM: terminating normally\n");
	exit(EXIT_SUCCESS);
}

/**
 * Handle SIGUSR1, an application specific signal. This handler
 * prints the current process id.
 */
void SIGUSR1_handler(int sig) {
	printf("Current process ID: %d\n", pid);
}

/**
 * Handle SIGUSR2, an application specific signal. This handler
 * prints the other process id.
 */
void SIGUSR2_handler(int sig) {
	printf("Other process ID: %d\n", otherPID);
}


/**
 * Display choices and waiting for input
 */
void display() {
	printf("0: quit\n");
	printf("1: SIGTSTP\n");
	printf("2: SIGCONT\n");
	printf("3: SIGTERM\n");
	printf("4: SIGUSR1\n");
	printf("5: SIGUSR2\n");
	printf("Please enter your choice: ");
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
   int status = 0;
   while(status == 0) {
	   // show choices
	   display();
	   int choice;
	   // keep asking for choice
	   printf("Please enter your choice:\n");
	   scanf("%d", &choice);
	   switch (choice) {
		   case 0:
			   printf("Program exiting\n");
			   return EXIT_SUCCESS;
		   case 1:
			   status = kill(otherPID, SIGTSTP);
			   break;
		   case 2:
			   status = kill(otherPID, SIGCONT);
			   break;
		   case 3:
			   status = kill(otherPID, SIGTERM);
			   break;
		   case 4:
			   status = kill(otherPID, SIGUSR1);
			   break;
		   case 5:
			   status = kill(otherPID, SIGUSR2);
			   break;
		   default:
			   printf("Please try again.\n");
	   }
   }
	printf("Error, process %d no longer exist\n", otherPID);
	return EXIT_FAILURE;
}


