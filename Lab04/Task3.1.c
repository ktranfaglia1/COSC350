// Kyle Tranfaglia
// COSC350 - Lab04
// Last updated 10/16/23
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

#define CHARSIZE 2048 // Sets size for char arrays

// Prototypes
void err_sys(char*);
void copyFile(int, int);

int main() {
	// Variables
	const char *home = getenv("HOME"); // Gets home directory
	char buffer1[CHARSIZE], buffer2[CHARSIZE];
	struct stat data;
	// Checks that home directory was captured
	if (home == NULL) {
		err_sys("Home not found");
	}

	umask(0000); // Clears permissions

	int inFile = open("hello", O_RDONLY); // Opens hello world file
	// Open file check
        if (inFile == -1) {
                err_sys("Open input file error");
        }
	// Moves to home directory with error check
	if (chdir(home) == -1) {
		err_sys("Move to home directory error");
	}
	// Checks if Dir1 exists, if not creates it with rwx permissions and error checks
	if (stat("Dir1", &data) < 0) {
		if (mkdir("Dir1", 0777) == -1) {
			err_sys("mkdir error 1");
		}
	}
	// Checks if Dir2 exists, if not creates it with rwx permissions and error checks
	if (stat("Dir2", &data) < 0) {
		if (mkdir("Dir2", 0777) == -1) {
			err_sys("mkdir error 2");
		}
	}
	// Checks if Dir2/Dir21 exists, if not creates it with rwx permissions and error checks
	if (stat("Dir2/Dir21", &data) < 0) {
		if (mkdir("Dir2/Dir21", 0777) == -1) {
			err_sys("mkdir error 3");
		}
	}
	int outFile = creat("Dir2/Dir21/hello", 0777); // Creates an output file to be copied
	// Checks that file was created and opened
	if (outFile == -1) {
		err_sys("Output file error");
	}

	copyFile(inFile, outFile); // Calls fucntion to copy the files

	close(inFile);
	close(outFile);

	sprintf(buffer1, "%s%s", home, "/Dir2/Dir21"); // Concatenates home diretcory and /Dir2/Dir21
	// Symbolic link todir21 to dir21
	if (symlink(buffer1, "Dir1/toDir21") < 0) {
		err_sys("symbolic link failed 1");
	}

	sprintf(buffer2, "%s%s", home, "/Dir2/Dir21/hello"); // Concatenates home directory and /Dir2/Dir21/hello

	// Symbolic link toHello to hello
	if (symlink(buffer2, "Dir1/toHello") < 0) {
		err_sys("symbolic link failed 2");
	}

	exit (0);
}
// Error Fucntion
void err_sys(char *str) {
        printf("%s\n", str);
        exit(1);
}
// Copy file function that takes in a 2 files, and copies the first to the second file
void copyFile(int inFile, int outFile) {
        char buffer[1]; // Buffer
        int bytes; // Byte counter
        // Loop to read in the file one byte at a time and write that to copy file with error checking
        while (bytes = read(inFile, buffer, 1 ) > 0) {
                if (write(outFile, buffer, bytes) != bytes) {
                        err_sys("Write error");
                }
        }
        // Check for read error
        if (bytes == -1) {
                err_sys("Read error");
        }
}
