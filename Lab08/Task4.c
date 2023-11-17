// Kyle Tranfaglia
// COSC350 - Lab08
// Last Updated 11/13/23
#include <signal.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXLINE 256
#define MAXINPUT 128

int main() {
	// Variables
	int fileDescriptor[2];
	char buffer[MAXLINE];
	pid_t pid;
	// Create pipe and check for pipe fail
	if (pipe(fileDescriptor) < 0) {
		perror("Pipe error\n");
		exit(1);
	}
	pid = fork(); // Fork teh processes
	// Check for fork error
	if (pid < 0) {
		perror("Fork error\n");
		exit(1);
	}
	// Child process
	if (pid == 0) {
		close(fileDescriptor[1]); // Close write
		int int1, int2; // Variables for inetegers to be summed
		// Read in data from the parent
		while (read(fileDescriptor[0], buffer, MAXLINE) > 0) {
			// Check for integers, and if they exist, assign to integer variables
			if (sscanf(buffer, "%d%d", &int1, &int2) == 2) {
				printf("Sum: %d\n", int1 + int2); // Sum and print
			}
			// Otherwise this is an invalid output
			else {
				printf("Invalid input\n");
			}
		}
		close(fileDescriptor[0]); // Close read
		kill(getppid(), SIGTERM); // Send kill signal to the parent
                exit(0);
	}
	// Parent process
	else {
		close(fileDescriptor[0]); // Close read
		char input1[MAXINPUT], input2[MAXINPUT]; // Variables to hold user input
		printf("Input 2 integers: \n");
		// Loop to continuously ask user for two integers as input
		while ((fgets(buffer, MAXLINE, stdin) != NULL)) {
			write(fileDescriptor[1], buffer, MAXLINE); // Write to buffer
		}
		close(fileDescriptor[1]); // Close write
	}
	exit(0);
}
