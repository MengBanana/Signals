# Signals

The SIGTSTP handler pauses the program
The SIGCONT handler redisplays the choices
The SIGTERM handler terminates the program< with exit status EXIT_SUCCESS./li>
The SIGUSR1 handler prints the curent process ID
The SIGUSR2 handler prints the other process ID
Then it displays its own process ID, and then prompts the user for a process ID of another process, which it stores in a static 
global variable otherPID.

Within a loop, It them presents a list of signals that it can send to the other process, including:

1 = SIGTSTP
2 = SIGCONT
3 = SIGTERM
4 = SIGUSR1
5 = SIGUSR2
The program offers "0 = quit" to quit the program with return value of EXIT_SUCCESS.
The program always sends the selected signal to the other process to handle. If the program receives an error return status (-1) 
from the kill() function, it should print "Process %d no longer available\n" with the other process id and quit the program with 
a return status of EXIT_FAILURE.

To test the program, run two instances of this program from two terminal windows. When promted, enter the process ID of the other process. 
Then input command choices to send signals to the other program and observe the results on the other console.
