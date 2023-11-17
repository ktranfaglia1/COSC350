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
	// Check number of arguements
	if (argc != 5) {
		err_sys("Incorrect number of arguements ... must provide 4 arguements");
	}
	pid_t pid;
	char *message;
	// Convert the strings to integers and save the arguements
	int exitCode = 0, n = 0, ns = 0, nc = myAtoi(argv[1]), np = myAtoi(argv[2]), tc = myAtoi(argv[3]), tp = myAtoi(argv[4]);

	printf("fork program starting\n");
	// Fork the process
	pid = fork();
	// Check which process
	switch (pid) {
		case -1:
			err_sys("fork failed"); // Fork fail case
		case 0: // Child case
			message = "This is the child";
			n = nc;
			ns = tc;
			exitCode = 42;
			break;
		default: // Parent case .. Default
			message = "This is the parent";
			n = np;
			ns = tp;
			exitCode = 0;
			break;
	}
	// If not child
	if (pid != 0) {
		int val = 0;
		pid_t childPid;

    		childPid = wait(&val); // Sets child with wait

    		printf("Child has finished: PID = %d\n", childPid); // Prints the child pid
		// Prints child exit code
    		if (WIFEXITED (val))
      			printf("Child exited with code %d\n", WEXITSTATUS(val));
    		else
      			printf("Child terminated abnormally\n");
  	}
	// Prints the message and sets the sleep
	for (; n > 0; n--) {
        	puts(message);
                sleep(ns);
        }
  	exit(exitCode);
}
void err_sys(char *str) {
        printf("%s\n", str);
        exit(1);
}
// Convertion function - string to integer
int myAtoi(char *str) {
        int result = 0;
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
