// Kyle Tranfaglia
// COSC 350 - Lab03
// Last Updated 10/02/23
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1
// Error Function
void err_sys(char *str) {
	printf ("%s",str);
	exit (1);
}

int main() {
	// Variables
	int bytes;
	char buffer[BUFFER_SIZE];
	// Reads in input file with a buffer of 1 until no characters left
	while ((bytes = read(STDIN_FILENO, &buffer, BUFFER_SIZE)) > 0)
		if (write (STDOUT_FILENO, &buffer, bytes) != bytes) // Checks that all that was read was written
			err_sys ("Write Error");
	if (bytes < 0) // Checks if error return on read
		err_sys("read Error");
	exit (0);
}
