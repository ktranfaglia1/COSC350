// Kyle Tranfaglia
// COSC350 - Lab09
// Last Updated 11/21/23
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define TFIFO "/tmp/task4_fifo" // Holds FIFO directory
#define READ_END 0 // Denotes pipe read
#define WRITE_END 1 // Denotes pipe write

int main() {
	// Create FIFO in program for convenience
	umask(0000);
	int fifoFD = mkfifo(TFIFO, 0777);

	// Variables
	const char data[] = "123";
	int processedData, fd, len = strlen(data);

	char *buffer = (char*)malloc(len); // Dynamically allocate a character array of size len (write data length)

	// Open FIFO with read and write and error check
	if ((fd = open(TFIFO, O_RDWR)) < 0) {
		printf("Error opening fifo\n");
		exit(1);
	}
	// Write data using FIFO
	processedData = write(fd, data, strlen(data));
	printf("Wrote %d bytes\n", processedData);

	// Read data using FIFO
	processedData = read(fd, buffer, len);
	printf("Read %d bytes: %s\n", processedData, buffer);

	close(fd); // Close FIFO
	free(buffer); // Free dynamically allocated memory
	exit(EXIT_SUCCESS);
}
