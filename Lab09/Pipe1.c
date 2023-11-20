// Kyle Tranfaglia
// COSC350 - Lab09
// Last Updated 11/20/23
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define READ_END 0 // Denotes pipe read
#define WRITE_END 1 // Denotes pipe write

int main() {
	// Variables
	const char data[] = "123"; // Input data
	int processedData, pipes[2], len = strlen(data); // Set len to data length
	char *buffer = malloc(len); // Dynamically allocated buffer

	// Do the pipe
	if (pipe(pipes) == 0) {
		processedData = write(pipes[WRITE_END], data, strlen(data)); // Write to pipe
		printf("Wrote %d bytes\n", processedData); // Print data wrote
		processedData = read(pipes[READ_END], buffer, len); // Read from pipe
		printf("Read %d bytes: %s\n", processedData, buffer); // print data read
		free(buffer); // Deallocate memory
		exit(EXIT_SUCCESS); // Success
	}
	exit(EXIT_FAILURE); // Fail
}
