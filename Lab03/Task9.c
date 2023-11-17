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
	printf("%s", str);
	exit(1);
}
int main(int argc, char *argv[]) {
	// Makes sure that 3 arguments are past like last program
	if (argc != 3) {
		err_sys("Incorrect number of arguments");
	}
	// Variables
	int inFile, outFile;
	char buffer[BUFFER_SIZE];
	int character = 0;

	inFile = open(argv[1], O_RDONLY); 
	outFile = open(argv[2], O_WRONLY | O_CREAT, 0666);
	// file validation check and dup2 success check
	if (inFile == -1 || outFile == -1)
		err_sys("File Open Error");

	if (dup2(outFile, STDOUT_FILENO) == -1)
		err_sys("Failed to redirect stdout");
	// reads in all characters one at a time with buffer and uses ASCII trick from previous program to convert back to the characters
	while (read(inFile, &buffer, BUFFER_SIZE) == 1) {
		if (buffer[0] == 10) {
			printf("\n");
		}
		else if (buffer[0] == 9) {
			printf("\t");
		}
		else {
			character = character * 10 + (buffer[0] - '0');
                        if (character >= 32 && character <= 126) {
                                printf("%c", character);
                                character = 0;
                	}

		}
	}

	dup2(STDOUT_FILENO, outFile); // Dups to the output file

	close(inFile);
	close(outFile);

	exit (0);
}
