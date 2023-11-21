// Kyle Tranfaglia
// COSC350 - Lab09
// Last Updated 11/21/23
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

#define READ_END 0
#define WRITE_END 1

int main() {
	// Variables
	int processedData, pipe1[2], pipe2[2];
	char data[] = "Hi there, Kiddo", buffer[BUFSIZ + 1];
	pid_t pid;

	memset(buffer, '\0', sizeof(buffer)); // Sets last position in buffer to end of string character

	// Do the pipes with error check
	if (pipe(pipe1) < 0) {
		printf("Error pipe\n");
		exit (1);
	}
	if (pipe(pipe2) < 0) {
		printf("Error pipe2\n");
		exit (1);
	}
	// Do the fork with error check
	pid = fork();
	if (pid == -1) {
		perror("Fork failure");
		exit(EXIT_FAILURE);
	}
	// Child Process
	else if (pid == 0) {
		// Get all the pipe information and send it to the child
		char p1in[BUFSIZ+1], p1out[BUFSIZ+1], p2in[BUFSIZ+1], p2out[BUFSIZ+1];

		// Set the last position of the character arrays to be end of string character
		memset(p1in, '\0', sizeof(p1in));
		memset(p1out, '\0', sizeof(p1out));
		memset(p2in, '\0', sizeof(p2in));
		memset(p2out, '\0', sizeof(p2out));

		// Assign variable to its corresponding pipe
		sprintf(p1in, "%d", pipe1[READ_END]);
		sprintf(p1out, "%d", pipe1[WRITE_END]);
		sprintf(p2in, "%d", pipe2[READ_END]);
		sprintf(p2out, "%d", pipe2[WRITE_END]);

		// Execute child program
		(void)execl("twoPipesChild", "twoPipesChild", p1in, p1out, p2in, p2out, (char *)0);

		exit(EXIT_FAILURE);
	}
	// Parent Process
	else {
		// Close read end for pipe 1 and close write for pipe2
		close(pipe1[READ_END]);
		close(pipe2[WRITE_END]);
		processedData = write(pipe1[WRITE_END], data, strlen(data));
		printf("%d - wrote %d bytes\n", getpid(), processedData);
		// Wait until child finishes process
		wait(&pid);
		processedData = read(pipe2[READ_END], buffer, BUFSIZ);
		printf("%d - read %d bytes: %s\n", getpid(), processedData, buffer);
	}
	exit(EXIT_SUCCESS);
}

