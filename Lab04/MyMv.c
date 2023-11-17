// Kyle Tranfaglia
// COSC350 - Lab04
// Last updated 10/16/23
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#define CHARSIZE 2048 // Sets size for buffers

// Prototypes
void err_sys(char*);
char* shiftStr(char*);

int main (int argc, char *argv[]) {
	// Command line argument validation
	if (argc < 3) {
		err_sys("Incorrect number of arguments ... must provide a file and a directory");
	}
	// Variables
	char *home = getenv("HOME");
	char buffer1[CHARSIZE], buffer2[CHARSIZE];
	struct stat data;

	// Checks if the argument includes ~/ and if so, replaces the symbol with the home directory
	if (*(argv[2]) == '~') {
		shiftStr(argv[2]); // Fucntion call to shift over the string to the left one to get rid of the ~/ symbol
		sprintf(buffer1, "%s%s", home, argv[2]); // Concatenates the home directory and the following path
	}
	else {
		sprintf(buffer1, "%s", argv[2]); // Copies the path to buffer without change
	}

	// Uses stat to check if the file exists
	if (stat(argv[1], &data) < 0) {
		err_sys("file does not exist");
	}
	// Checks if the destination exists, and if so, checks more criteria, otherwise copies buffer1 to buffer2, as in do not change anything
	if (stat(buffer1, &data) >= 0) {
		// Checks if it is a directory, and if so, concatenates the directory with home and file, otherwise, copies the directory
		if (S_ISDIR(data.st_mode)) {
			sprintf(buffer2, "%s%s%s", buffer1, "/", argv[1]);
		}
		else {
			sprintf(buffer2, "%s", buffer1);
		}
	}
	else {
		sprintf(buffer2, "%s", buffer1); // Copies directory if alteration is not needed, location does not exist 
	}
	// Links the file and the directory with error check
	if (link(argv[1], buffer2) < 0) {
		err_sys("Link failed");
	}
	// Unlinks the file from its previous location with error check
	if (unlink(argv[1]) < 0) {
		err_sys("Unlink failed");
	}
	// Move completed ... link set file to new location and unlink removed location file was previously
	exit (0);
}
// Error Function
void err_sys(char *str) {
        printf ("%s\n", str);
        exit (1);
}
// Function to shift a string left by one index
char* shiftStr(char *str) {
        // Starting from the left, shift each postion left one index such that the first index is removed and the array shrinks by one
        for (int i = 1; str[i] != '\0'; i++) {
                str[i-1] = str[i];
        }
        return str;
}
