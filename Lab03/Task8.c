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
	printf("%s\n", str);
	exit(1);
}
int main(int argc, char *argv[]) {
	// Checks that there are three incoming parameters (program, inputfile, outputfile)
	if (argc != 3) {
		err_sys("Incorrect Number of arguments");
	}

	umask(0); // Clears umask permissions
	// Variables
	int inFile, outFile;
	char buffer[BUFFER_SIZE];

	inFile = open(argv[1], O_RDONLY); 
	outFile = open(argv[2], O_WRONLY | O_CREAT, 0666);
	// Input validation for input files and checks that the dup was a success
	if (inFile == -1 || outFile == -1)
		err_sys("File Open Error");

	if (dup2(outFile, STDOUT_FILENO) == -1) {
		err_sys("Redirect Fail");
	}

	dup2(outFile, STDOUT_FILENO);

	while(read(inFile, &buffer, BUFFER_SIZE) > 0) { //reads in every char
		if (buffer[0] == '\n') // Takes care of newline 
			printf("\n");
		else if (buffer[0] == '\t')
			printf("\t");
		else
			printf("%d", buffer[0]); // Converts to ASCII
	}
	close(inFile);
	close(outFile);

	exit (0);
}
