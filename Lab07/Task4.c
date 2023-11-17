// Kyle Tranfaglia
// COSC350 - Lab07
// Last Updated 10/30/23
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

static int sig1 = 0, sig2 = 0; // Static variables to hold trigger status of signals

// Prototype
void ProcessSignal(int);

int main() {
	// Set up the signals to be handled by ProcessSignal function
	signal(SIGUSR1, &ProcessSignal);
	signal(SIGUSR2, &ProcessSignal);

	pid_t pid, pidc; // Process ID variables ... child and other child

	pid = fork(); // Fork processes ... first child created
	// Checks for fork error
	if (pid == -1) {
		perror("Fork error");
		exit(1);
	}
	// Parent process
	if (pid != 0) {
		waitpid(pid, 0, 0); // Wait for the child
		pidc = fork(); // Fork process ... second child created
		// Checks for fork error
		if (pidc == -1) {
			perror("Fork error");
			exit(2);
		}
	}
	// Child process
	if (pid == 0) {
		kill(getppid(), SIGUSR1); // Send signal to parent, handled but signal setup ... calls ProcessSignal with signal
		exit(0);
	}
	else if (pidc == 0) {
		kill(getppid(), SIGUSR2); // Send signal to parent, handled but signal setup ... calls ProcessSignal with signal
		exit(0);
	}
	else {
		waitpid(pidc, 0, 0); // Wait for the second child
	}
	return 0;
}
// Function to process the signals
void ProcessSignal(int sig) {
	// Prints upon death of first child
        if (sig == SIGUSR1) {
                printf("Hi Honey! Anything Wrong?\n");
		sig1= 1;
        }
	// Prints upon death of second child
        else if (sig == SIGUSR2) {
                printf("Do you make trouble again?\n");
		sig2 = 1;
        }
}
