// Kyle Tranfaglia
// COSC350 - Lab09
// Last Updated 11/21/23
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define READ_END 0 // Denotes pipe read
#define WRITE_END 1 // Denotes pipe write

int main(int argc, char *argv[]) {
	// Variables
	int processedData, fd1[2], fd2[2];
	char buffer[BUFSIZ + 1], data[] = "Hi, Mom";

	// Convert the arguments to int
	sscanf(argv[1], "%d", &fd1[READ_END]);
	sscanf(argv[2], "%d", &fd1[WRITE_END]);
	sscanf(argv[3], "%d", &fd2[READ_END]);
	sscanf(argv[4], "%d", &fd2[WRITE_END]);

	memset(buffer, '\0', sizeof(buffer)); // Add end of string character to end of buffer

	// Close the pipe ends
	close(fd1[WRITE_END]);
	close(fd2[READ_END]);

	// Read from the first pipe
	processedData = read(fd1[READ_END], buffer, BUFSIZ);
	printf("%d - read %d bytes: %s\n", getpid(), processedData, buffer);

	// Write to the second pipe
	processedData = write(fd2[WRITE_END], data, strlen(data));
	printf("%d - wrote %d byes\n", getpid(), processedData);
	exit(EXIT_SUCCESS);
}
