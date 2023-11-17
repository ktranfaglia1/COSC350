// Kyle Tranfaglia
// COSC350 - Lab07
// Last Updated 10/30/23
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

// Prototypes
void killParent(int);
void killChild(int);

int main() {
	// Set the signal to call corresponding kill fucntions on reception
	signal(SIGUSR1, killChild);
	signal(SIGUSR2, killParent);

	// Variables for process IDS
	pid_t pid, gcpid;
	pid = fork(); // Fork processes ... creates child
	// Check fork error
	if (pid == -1) {
		perror("Fork error");
		exit(1);
	}
	// Child process
	else if (pid == 0) {
		gcpid = fork(); // Fork Processes ... creates grandchild
		// Grandchild process
		if (gcpid == -1) {
			perror("Fork error");
			exit(2);
		}
		else if (gcpid == 0) {
			// Prints Grandchild process 10 times
			int count = 0;
			pid_t currentParent, previousParent = getppid();
			while (1) {
				printf("Grandchild Process\n");
				if (count == 9) {
					kill(getppid(), SIGUSR1); // Sends signal to child so that it is killed
				}
				count++;
				currentParent = getppid();
				if (currentParent != previousParent) {
					exit(0);
				}
			}
		}
		// Child process
		else {
			// Child process runs until signal kills it
			while (1) {
				printf("Child Process\n");
			}
		}
	}
	// Parent process
	else {
		while (1) {
			printf("Parent Process\n");
		}
	}
	exit(0);
}
// Function to handle parent death ... Lets user know and exits
void killParent(int sig){
        // printf("Parent Killed!\n");
        exit(0);
}
// Function to kill the child process, inform the user of child death, and send death signal to parent, then exit
void killChild(int sig){
        // printf("Child Killed!\n");
        kill(getppid(), SIGUSR2);
        exit(0);
}
