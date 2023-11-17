/ Kyle Tranfaglia
// COSC 350 - Lab03
// Last Updated 10/02/23
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 1
// Error Function
void err_sys(char *str) {
        printf("%s\n",str);
        exit (1);
}

int main() {
	// Variables
        int bytes;
        char buffer[BUFFER_SIZE], inFileName[256], outFileName[256];
	struct stat buf;

        umask(0); // Clears umask permissions

        printf("Enter a readable file: \n"); // prompts user
        scanf("%s", inFileName); // reads in the file name given by user
	// Input validation for input file
        if (access(inFileName, F_OK) != 0) {
                err_sys("File does not exist");
        }
        if (access(inFileName, R_OK) != 0) {
                err_sys("File is not readable");
        }

        int inFile = open(inFileName, O_RDONLY); //Opens the read file

        printf("Enter an output file for copying: \n"); // prompts user
        scanf("%s", outFileName); // reads in the file that data should be sent too
	// Checks if the input and output file are the same
	if (strcmp(inFileName, outFileName) == 0) {
                err_sys("Cannot use input file as output file");
        }

        int outFile = open(outFileName, O_WRONLY|O_CREAT, 0770); //opens file used for outputting

	fstat(inFile, &buf);
	off_t size = buf.st_size; // Gets file size for loop
	// loop to go through the file simialr to previous program but uses pread instead, providing i to traverse file from that position
        for (int i = size - 2; i >= 0; i--) {
       		if((bytes = pread(inFile, &buffer, BUFFER_SIZE, i)) < 0) {
            		err_sys("Read error");
        	}
        	if((bytes = write(outFile, &buffer, BUFFER_SIZE)) < 0) {
           		err_sys("Write error");
        	}
    	}

        close(inFile);
        close(outFile);
        exit (0);
}