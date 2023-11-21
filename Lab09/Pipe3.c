// Kyle Tranfaglia
// COSC350 - Lab09
// Last Updated 11/20/23
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

#define READ_END 0 // Denotes pipe read
#define WRITE_END 1 // Denotes pipe write

int main() {
	// Variables
	int processedData, pipes[2];
	const char data[] = "123"; // Input data
	char buffer[BUFSIZ+1]; // Set buffer of max size (plus 1 for end string)
	pid_t pid;

	memset(buffer, '\0', sizeof(buffer)); // Place end string character at end of buffer
	// Create pipe
	if (pipe(pipes) == 0) {
		pid = fork(); // Fork processes
		// Fork error
		if (pid == -1) {
			perror("Fork failure");
			exit(EXIT_FAILURE);
		}
		// Child process
		else if (pid == 0) {
			close(pipes[READ_END]); // Close pipe read
			sprintf(buffer, "%d", pipes[0]); // read pipe data to buffer
			(void)execl("Pipe4", "Pipe4", buffer, (char *)0); // Execute pipe4
			exit(EXIT_FAILURE);
		}
		// Parent Process
		else {
			wait(NULL); // Wait for child to finish
			close(pipes[WRITE_END]); // Close pipe write
			processedData = write(pipes[WRITE_END], data, strlen(data)); // Write data to pipe
			printf("%d - wrote %d bytes\n", getpid(), processedData); // Print what was wrote
		}
	}
	exit(EXIT_SUCCESS);
}
