// Kyle Tranfaglia
// COSC350 - Lab07
// Last Updated 10/30/23
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1

int main() {
	// Variables
	pid_t pid;
	int status, file, bytes;
	char buffer[BUFFER_SIZE];

	file = open("foo", O_RDWR | O_CREAT, 0666);

	pid = fork(); // Forks process .. child created
	// Fork failed
	if (pid == -1) {
		perror("fork error");
		exit(1);
	}
	// Child process
	else if (pid == 0) {
		umask(0000); // Clears permissions
		// file = open("foo", O_WRONLY | O_CREAT, 0666); // Creates file foo with -rw-rw-rw-
		// Writes message to foo and checks that all of the message was written
		if (write(file, "Hi, Mom\n", 8) != 8) {
			perror("Write error");
			exit(2);
		}
		lseek(file, 0, SEEK_SET);
	}
	// Parent process
	else {
		wait(&status); // Wait for child to finish
		// Write message to standard output (terminal) and check that all of the message was written
		if (write(1, "My son said ", 12) != 12) {
			perror("Write error");
			exit(3);
		}
		// file = open("foo", O_RDONLY); // Opens the foo file
		// Read from foo file and write all of its contents one byte at a time to standard out (terminal) and error check write
		while ((bytes = read(file, buffer, BUFFER_SIZE)) > 0) {
			if (write(1, buffer, bytes) != bytes) {
				perror("Write error");
				exit(4);
			}
		}
		// Read error check
		if (bytes == -1) {
			perror("Read Error");
			exit(5);
		}
	}
	close(file); // Close file
	exit(0);
}
