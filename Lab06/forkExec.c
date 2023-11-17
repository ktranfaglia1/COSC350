// Kyle Tranfaglia
// COSC350 - Lab06
// Last Updated 10/23/23
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

// Prototypes
void err_sys(char *);
int myAtoi(char *);

int main(int argc, char *argv[]) {
	// Arguement number check
	if (argc != 5) {
		err_sys("Incorrect number of arguments ... must provide 4 arguments");
	}
	// Variables
	pid_t pid, pidChild, pidParent;
	char message[50];
	int n, ns, exitCode = 0, np = myAtoi(argv[2]), tp = myAtoi(argv[4]);

	printf("fork program starting\n");
	// Start fork
	pid = vfork();
	switch(pid) {
		case -1: // Fail case

			err_sys("fork failed");
		case 0: // Child case
			// Gets child pid
			pidChild = getpid();
			// Copy the message to message
			sprintf(message, "This is the child with pid = %d", pidChild);
			// Execute the file
			if (execl("/mnt/linuxlab/home/ktranfaglia1/COSC350/Lab06/child", message, argv[1], argv[3], (char *)0) < 0) {
				err_sys("exec error\n");
			}
			break;
		default: // Parent case .. Default
			pidParent = getpid();
			//Copy the message
			sprintf(message, "This is the parent with pid = %d", pidParent);
			n = np;
			ns = tp;
			exitCode = 0;
			// Puts the message on the screen and sleep
			for(; n > 0; n--){
				puts(message);
				sleep(ns);
			}
			break;
	}
	// If not child
	if (pid != 0) {
		int val = 0;
		pid_t childPid;

    		childPid = wait(&val); // Set child using wait

    		printf("Child has finished: PID = %d\n", childPid); // Print child ID
		// Print child exit code
    		if (WIFEXITED (val))
      			printf("Child exited with code %d\n", WEXITSTATUS(val));
    		else
      			printf("Child terminated abnormally\n");
  	}
  	exit(exitCode);
}
// Error Function
void err_sys(char *str) {
        printf("%s\n", str);
        exit(1);
}
// Convertion function - string to integer
int myAtoi(char *str) {
        int result = 0;
	// If negative move along to ignore it
	if (*str == '-') {
		str++;
	}

        // Loop to run for as long as integers are read in
        while (*str <= '9' && *str >= '0') {
                result = result * 10 + (*str - '0');
                str++;
        }

        return result;
}
