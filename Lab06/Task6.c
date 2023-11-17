// Kyle Tranfaglia
// COSC350 - Lab06
// Last updated 10/23/23
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1

// Prototype
void err_sys(char *);

int main(int argc, char **argv) {
 	// Check number of argument
	if (argc != 2) {
		err_sys("Need 1 argument");
  	}
	// Variables
 	char *fileName = argv[1];
	int inFile, outFile, bytes = 0;
	char buffer[BUFFER_SIZE];
	pid_t pid;

	//Open the file
	inFile = open(fileName, O_RDONLY);
	// Get the end and offset
	int end = lseek(inFile, 0, SEEK_END);
	int offset = lseek(inFile, 0, SEEK_SET);
  	// Reset permission
  	umask(0000);

	// Fork processes
  	pid = fork();
	// Check fork error
  	if (pid == -1) {
    		err_sys("fork error");
  	}
 	else if (pid == 0) { // If child
      		// Open up child file
      		outFile = open("child.txt", O_WRONLY | O_CREAT, 0666);
      		// Read and write until end of the file
      		while (end > offset) {
      			bytes = read(inFile, buffer, BUFFER_SIZE);
			// Only write if is not numeric
      			if (buffer[0] < '0' || buffer[0] > '9') {
        			write(outFile, buffer, bytes);
			}
      		offset++;
      		}
		// Check read error
		if (bytes == -1) {
			err_sys("Read error");
		}
    	close(outFile);
	}
 	else { // If parent
      		// Open up parent file
      		outFile = open("parent.txt", O_WRONLY | O_CREAT, 0666);
      		// Read and write until end of the file
      		while (end > offset) {
     			bytes = read(inFile, buffer, BUFFER_SIZE);
			// Only write if numeric or new line
      			if (buffer[0] >= '0' && buffer[0] <= '9' || buffer[0] == '\n') {
        			write(outFile, buffer, bytes);
			}
      		offset++;
      		}
		// Check read error
		if (bytes == -1) {
			err_sys("Read error");
		}
	close(outFile);
    	}
	close(inFile);
	exit(0);
}
// Error Function
void err_sys(char *str) {
        printf("%s \n", str);
        exit (1);
}
