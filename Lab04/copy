// Kyle Tranfaglia
// COSC350 - Lab04
// Last updated: 10/09/23
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFER_SIZE 1
// Error Function
void err_sys(char *str) {
        printf ("%s\n",str);
        exit (1);
}
int main(int argc, char* argv[]) {
	// Validation check for proper number of arguments
	if (argc != 6) {
		err_sys("Invalid number of arguments ... must enter five file names");
	}

	umask(0000); // Clears umask permissions

	// Opens all files and sets permissions for output files as 0777
	int inFile = open(argv[1], O_RDONLY);
	int charFile = open(argv[2], (O_CREAT | O_RDWR), 0777);
	int numFile = open(argv[3], (O_CREAT | O_RDWR), 0777);
	int otherFile = open(argv[4], (O_CREAT | O_RDWR), 0777);
	int copyFile = open(argv[5], (O_CREAT | O_RDWR), 0777);
	// Error checks all files to make sure they opened
	if (inFile == -1 || charFile == -1 || numFile == -1 || otherFile == -1 || copyFile == -1) {
		err_sys("Open file error");
	}
	// Variables
	char buffer[BUFFER_SIZE], buffer1[BUFFER_SIZE], buffer2[BUFFER_SIZE], buffer3[BUFFER_SIZE];
	char space[1];
	int num = 0, bytes = 0, bytes2 = 0, bytes3 = 0, bytes4 = 0, status = 0;

	space[0] = ' ';
	// Loop to read through the entire input file one byte at a time
	while ((bytes = read(inFile, buffer, BUFFER_SIZE)) > 0) {
		num = (int) buffer[0]; // Converts ASCII character to ASCII numeric value
		// Checks ASCII values for numbers and writes to file with error check
		if (num >= 48 && num <= 57) {
			if (write(numFile, buffer, bytes) != bytes) {
				err_sys("Write error");
			}
		}
		else { // Otherwise write a space to the file
			if (write(numFile, space, 1) != 1) {
				err_sys("Write error");
			}
		}
		// Checks ASCII values for alphabetical characters and writes to file with error check
		if (num >= 65 && num <= 122) {
			if (write(charFile, buffer, bytes) != bytes) {
                                err_sys("Write error");
                        }
		}
		else { // Otherwise write a space to the file
			if (write(charFile, space, 1) != 1) {
				err_sys("Write error");
			}
		}
		// Checks ASCII values for all other characters and writes to file with error check
		if ((num >= 0 && num <= 47) || (num >= 58 && num <= 64) || (num >= 123 && num <= 127)) {
			if (write(otherFile, buffer, bytes) != bytes) {
                                err_sys("Write error");
                        }
		}
		else { // Otherwise write a space to the file
			if (write(otherFile, space, 1) != 1) {
				err_sys("Write error");
			}
		}
	}
	// Checks for read error
	if (bytes == -1) {
		err_sys("Read error");
	}
	// Close input file and move file pointer to beginning for rest of files
	close(inFile);
	lseek(numFile, 0, SEEK_SET);
	lseek(charFile, 0, SEEK_SET);
	lseek(otherFile, 0, SEEK_SET);
	// Loop to copy the contents of input file to copy file by only using the number, character, and other files filled in previous loop
	while ((bytes4 = read(charFile, buffer1, BUFFER_SIZE)) > 0) {
		status = 0; // Status variable to denote an if statment being true
		// If statements check that the buffer value is not a space for each file and if so writes to copy file, otherwise if false for all, write a space to copy file ... Write error checking for all statments
		if (buffer1[0] != space[0]) {
			status = 1;
			if (write(copyFile, buffer1, bytes4) != bytes4) {
				err_sys("Write error");
			}
		}
		if ((bytes2 = read(numFile, buffer2, BUFFER_SIZE)) > 0) {
			if (buffer2[0] != space[0]) {
				status = 1;
                        	if (write(copyFile, buffer2, bytes2) != bytes2) {
                        	        err_sys("Write error");
                        	}
                	}
		}
		if ((bytes3 = read(otherFile, buffer3, BUFFER_SIZE)) > 0) {
                        if (buffer3[0] != space[0]) {
				status = 1;
                                if (write(copyFile, buffer3, bytes3) != bytes3) {
                                        err_sys("Write error");
                                }
                        }
                }

		if (!status) {
			 if (write(copyFile, space, 1) != 1) {
                         	err_sys("Write error");
                         }
		}
	}
}
