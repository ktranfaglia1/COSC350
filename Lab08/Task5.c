// Kyle Tranfaglia
// COSC350 - Lab08
// Last Updated 11/13/23
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char**argv) {
	int argSize = 0; // Variable to hold argument size
	// Loop to get argument size by getting a running total of the string lenth of each argument
	for (int i = 1; i < argc; i++) {
		argSize += strlen(argv[i]);
	}
	char *command = malloc(argSize*sizeof(char)); // Dynamically allocate a char array of argument size
	// Concatenate all the arguments into dynamic array with sprintf
	for (int i = 1; i < argc; i++) {
		sprintf(command, "%s %s", command, argv[i]);
	}
	FILE *ptr; // Popen
	char buffer[BUFSIZ]; // Create buffer of max buffer size
	// Open popen with read only
	if ((ptr = popen(command, "r")) != NULL) {
		// Gets the buffer from the pipe and print the buffer
		while (fgets(buffer, BUFSIZ, ptr) != NULL) {
			printf("%s", buffer);
		}
	}
	pclose(ptr); // Close the pipe
	exit(0);
}
