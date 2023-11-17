// Kyle Tranfaglia
// COSC350 - Lab07
// Last Updated 10/30/23
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int alarm_fired = 0; // Static variable to hold alarm status

// Signal handler for SIGALRM
void ding(int sig) {
	alarm_fired = 1;
}

int main() {
	pid_t pid; // Process ID varibale

	struct sigaction signal; // Signal structure
	signal.sa_handler = ding; // Lets the function ding handle the signals caught by sigaction
	printf("alarm application starting\n");

	pid = fork(); // Forks process, child created
	// Checks if process is parent or a failed fork
	switch (pid) {
		case -1: /* failure */
			perror("forkerror");
			exit(1);
		case 0: /* child */
			sleep(5);
			kill(getppid(), SIGALRM); // Kills child after 5 seconds
			_exit(0); // Exit ... sends signal of child death
	}
	/* If we get here we are the parent process */
	printf("waiting for alarm to go off\n");
	sigaction (SIGALRM, &signal, 0); // Signal for alarm to go off ... specifies handling
	pause();
	// Prints a ding if alarm is triggered
	if (alarm_fired) {
		printf("Ding!\n");
	}
	printf("done\n");
	exit(0);
}
