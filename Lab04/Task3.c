// Kyle Tranfaglia
// COSC320 - Lab04
// Last updated 10/10/23
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

// Prototypes
void err_sys(char*);
int palind(int, int);

int main(int argc, char *argv[]) {
	// Check that valid number of arguments were passed
	if (argc != 2) {
		err_sys("Invalid number of arguments ... must provide one input file");
	}
	int inFile = open(argv[1], O_RDONLY); // Opens the file given as command line argument
	int copyFile = dup(inFile); // Duplicates the file in copy file

	// Checks for open file error
	if (inFile == -1) {
	       err_sys("Open file error");
	}
	// Checks for copy file duplication error
	if (copyFile == -1) {
		err_sys("Duplication error");
	}
	// Checks if palindrome with function returning 1 on true and prints accordingly
	if (palind(inFile, copyFile)) {
		printf("File contains a palindrome\n");
	}
	else {
		printf("File does not contain a palindrome\n");
	}

	// Close the files
	close(inFile);
	close(copyFile);

	exit (0);
}
// Error Function
void err_sys(char *str) {
        printf("%s\n", str);
        exit(1);
}
// Palindriome fucntion to take in two file descriptors to the same file and check for palindrome ... returns 1 if true, 0 if false
int palind(int fd1, int fd2) {
	// Variables
        int offset = 0, status = 0, count = 0;
        char buffer1, buffer2;

	// One byte read of first file with error check
	if (read(fd1, &buffer1, 1) == -1) {
		err_sys("Read Error");
	}
	// Moves the file cursor to end of file and back two so it is on the first non-eof and end of string character
	if ((count = lseek(fd2, -2, SEEK_END)) == -1) {
		err_sys("Seek Error");
	}
	// One byte read of second file with error check
	if (read(fd2, &buffer2, 1) == -1) {
		err_sys("Read Error");
	}
	// Loop to read through the files until the buffers do not equate or the halfway point is reached
	while (buffer1 == buffer2 && offset < count) {
		// Increment offset for first file and set to that position and error check
		if (lseek(fd1, ++offset, SEEK_SET) == -1) {
			err_sys("Seek Error1");
		}
		// Read one byte of first file with error check
		if (read(fd1, &buffer1, 1) == -1) {
			err_sys("Read Error");
		}
		// Decrement count for second file and set to that position and error check
		if (lseek(fd2, --count, SEEK_SET) == -1) {
			err_sys("Seek Error2");
		}
		// Read one byte of the second file with error check
		if (read(fd2, &buffer2, 1) == -1) {
			err_sys("Read Error");
		}
	}
        // Checks if the buffer is same after loop, if so, it is a palindrome as the loop terminated after confirming equality until the middle and not an inequality between the buffers
        if (buffer1 == buffer2) {
                status = 1;
        }
	return status;
}
