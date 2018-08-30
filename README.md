# Signals
By running two instances of this program interminal, they can control each other by sending signals.
The program will firstly display its owne process ID, and then prompts the user for the process ID of
the other process.

The SIGTSTP handler pauses the program

The SIGCONT handler redisplays the choices

The SIGTERM handler terminates the program< with exit status EXIT_SUCCESS./li>

The SIGUSR1 handler prints the curent process ID

The SIGUSR2 handler prints the other process ID

Within a loop, It then presents a list of signals that it can send to the other process, including:
The program offers "0 = quit" to quit the program with return value of EXIT_SUCCESS.
The program always sends the selected signal to the other process to handle. If the program receives an error return status (-1) 
from the kill() function, it should print "Process %d no longer available\n" with the other process id and quit the program with 
a return status of EXIT_FAILURE.

