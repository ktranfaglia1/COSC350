// Kyle Tranfaglia
// COSC350 - Lab06
// Last Updated 10/23/23
#include <utmp.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

// Prototypes
int openUtmpFile();
void err_sys(char *);

int main() {
	// Variables
	int bytes = 0, count = 0, utmpFileDescriptor = openUtmpFile();
	struct utmp data;
	// Reads utmp file and prints users and gets number of logged-in users
	while (bytes = read(utmpFileDescriptor, &data, sizeof(data)) > 0) {
		printf("Username: %s \n", data.ut_user);
		if (data.ut_type == USER_PROCESS) {
			count++;
		}
	}
	printf("Number of Logged-in Users: %d \n", count); // Prints number of logged-in users

	close(utmpFileDescriptor);
	exit (0);
}
// Error Function
void err_sys(char *str) {
        printf("%s \n", str);
        exit (1);
}
// Function to open utmp file
int openUtmpFile() {
	int utmpFile = open("/var/run/utmp", O_RDONLY); // Open utmp file
	// Check if file opened
	if (utmpFile == -1) {
		err_sys("Open utmp error");
	}
	return utmpFile;
}
