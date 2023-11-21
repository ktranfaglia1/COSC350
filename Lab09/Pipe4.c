// Kyle Tranfaglia
// COSC350 - Lab09
// Last Updated 11/20/23
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	// Variables
	int processedData, fd;
	char buffer[BUFSIZ + 1];

	memset(buffer, '\0', sizeof(buffer)); // Set last character of buffer to end string character
	sscanf(argv[1], "%d", &fd); // Get command line arguement
	processedData = read(fd, buffer, BUFSIZ); // Read data

	printf("%d - read %d bytes: %s\n", getpid(), processedData, buffer); // Print read data
	exit(EXIT_SUCCESS);
}
