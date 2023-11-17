// Kyle Tranfaglia
// COSC350 - Lab06
// Last Updated 10/23/23
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

extern char **environ; // Gets enviornmental variables as array from system

// Prototypes
void err_sys(char*);
int isEqual(char*, char*);
char* mygetenv(char*);

int main(int argc, char *argv[]) {
	// Arguement check
	if (argc != 2) {
		err_sys("Incorrect number of arguements ... must provide one arguement");
	}

	printf("%s \n", mygetenv(argv[1])); // Print envrionment variable
	exit (0);
}
// Error Function
void err_sys(char *str) {
	printf("%s \n", str);
	exit (1);
}
// Function to compare two char arrays
int isEqual(char *str1, char *str2) {
	int status = 1;
	// Compares characters in array until not equal
	while (*str1 == *str2 && *(str1 + 1) != '=') {
		str1++;
		str2++;
	}
	// If not equal then the strings must not be equal
	if (*str1 != *str2) {
		status = 0;
	}
	return status;
}
// Function to get enviornmental variable
char* mygetenv(char *str) {
	// Grab the systems environment variable list
	char **listptr = environ;
	// While the pointer is not null and the strings are not equal, traverse list
	while (*listptr != NULL && !isEqual(*listptr, str)) {
		listptr++;
	}

	// If end of list reached, then not in list
	if (*listptr == NULL) {
		err_sys("Invalid path name");
	}

	char *env = *listptr; // Sets a pointer to the char array in the list
	// Traverses char array until '=' is reached and then returns one beyond index of '='
	while (*env != '=') {
		env++;
	}

	return ++env;
}
