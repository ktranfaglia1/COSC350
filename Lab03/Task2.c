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
	scanf("%s", inFileName); // Reads in the file name for input
	// file input validation
	if (access(inFileName, F_OK) != 0) {
		err_sys("File does not exist");
	}
	if (access(inFileName, R_OK) != 0) {
		err_sys("File is not readable");
	}

	int inFile = open(inFileName, O_RDONLY); // Opens the read file

	printf("Enter an output file for copying: \n"); // prompts user
	scanf("%s", outFileName); // Reads in the file for output

	if (strcmp(inFileName, outFileName) == 0) {
                err_sys("Cannot use input file as output file");
        }

	int outFile = open(outFileName, O_WRONLY|O_CREAT, 0666); // Opens fil for outputting
	
        // Reads in input file with a buffer of 1 until no characters left
        while ((bytes = read(STDIN_FILENO, &buffer, BUFFER_SIZE)) > 0)
                if (write (STDOUT_FILENO, &buffer, bytes) != bytes) // Checks that all that was read was written
                        err_sys ("Write Error");
        if (bytes < 0) // Checks if error return on read
                err_sys("read Error");


	close(inFile);
	close(outFile);

        exit (0);
}
