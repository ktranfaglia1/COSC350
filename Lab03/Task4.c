// Kyle Tranfaglia
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
	// checks if input and output file are the same
	if (strcmp(inFileName, outFileName) == 0) {
                err_sys("Cannot use input file as output file");
        }
	if (access(outFileName, F_OK) == 0) {
                chmod(outFileName, 0760);
        }

        int outFile = open(outFileName, O_WRONLY|O_CREAT, 0760); //opens file used for outputting
	lseek(outFile, 0, SEEK_END); // Moves cursor to end
	// Same read and wriet loop from previous programs
        while ((bytes = read(inFile, &buffer, BUFFER_SIZE)) > 0)
                if (write(outFile, &buffer, bytes) != bytes)
                        err_sys("Write Error");
        if (bytes < 0)
                err_sys("Read Error");

	printf("Enter another readable file: \n"); // prompts user
        scanf("%s", inFileName); // reads in the file name given by user

	if (strcmp(inFileName, outFileName) == 0) {
                err_sys("Cannot use output file as input file");
        }
        if (access(inFileName, F_OK) != 0) {
                err_sys("File does not exist");
        }
        if (access(inFileName, R_OK) != 0) {
                err_sys("File is not readable");
        }

        inFile = open(inFileName, O_RDONLY); //Opens the read file
	lseek(outFile, 0, SEEK_END);

	while ((bytes = read(inFile, &buffer, BUFFER_SIZE)) > 0)
                if (write(outFile, &buffer, bytes) != bytes)
                        err_sys("Write Error");
        if (bytes < 0)
                err_sys("Read Error");

        close(inFile);
        close(outFile);
        exit (0);
}

