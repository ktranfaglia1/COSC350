// Kyle Tranfaglia
// COSC350 - Lab06
// Last Updated 10/23/23
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1

// Prototypes
void err_sys(char *);
int isDigit(char c);

int main(int argc, char **argv) {
 	// Check for number of arguements
	if (argc != 2) {
		err_sys("Incorrect number of arguements ... Need 1 arguement");
  	}
	// Variables
	char buffer[BUFFER_SIZE];
	int inFile, outFile1, outFile2, offset = 0;
	// Clearing umask
        umask(0000);
	// Open input file and check for error
	inFile = open(argv[1], O_RDONLY);
	if (inFile == -1) {
		err_sys("File open error\n");
	}

	pid_t pid;
        pid = fork(); // Fork processes

	// Opening out files and checking for error, permissions set as rw-rw-rw
	if (pid != 0) {
		outFile1 = open("parent.txt", O_WRONLY | O_CREAT, 0666);
		if (outFile1 == -1) {
			err_sys("Create file error\n");
		}
	}
	else {
		outFile2 = open("child.txt", O_WRONLY | O_CREAT, 0666);
		if (outFile2 == -1) {
			err_sys("Create file error\n");
		}
	}

	// Traverse and read files with pread and write if meets requirments
	while (pread(inFile, buffer, BUFFER_SIZE, offset) > 0) {
		// If child
		if (pid == 0) {
			// Check if character is not a digit or new line, if so,  writes to child.txt
			if (!isDigit(buffer[0]) || buffer[0] == '\n') {
				write(outFile2, buffer, BUFFER_SIZE);
			}
		}
		else {
			// Check if character is a number or new line, if so, writes to parent.txt
			if (isDigit(buffer[0]) || buffer[0] == '\n') {
				write(outFile1, buffer, BUFFER_SIZE);
			}
		}
		offset++;
	}
	close(inFile);
	close(outFile1);
	close(outFile2);

	exit(0);
}
// Error Function
void err_sys(char *str) {
        printf("%s \n", str);
        exit (1);
}
// Function to check if a character is a digit
int isDigit(char c) {
	int status = 0; // Defaults to false
	// If numeric, set to true
	if (c >= '0' && c <= '9') {
		status = 1;
	}
	return status;
}
