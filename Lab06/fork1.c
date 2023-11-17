// Kyle Tranfaglia
// COSC350 - Lab06
// Last Updated 10/23/23
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Prototypes
void err_sys(char *);
int myAtoi(char *);

int main(int argc, char *argv[]) {
	// Checks number of arguements
	if (argc != 5) {
		err_sys("Incorrect number of arguements ... must provide 4 arguements");
	}
	pid_t pid;
	char *message;
	// Convert the strings to integers and saves arguements
	int n = 0, ns = 0, nc = myAtoi(argv[1]), np = myAtoi(argv[2]), tc = myAtoi(argv[3]), tp = myAtoi(argv[4]);

	printf("fork program starting\n");
	// Fork the process
	pid = fork();
	// check which process
	switch (pid) {
		case -1:
			err_sys("fork failed"); // Print error case
		case 0: // Child case
			message = "This is the child";
			n = nc;
			ns = tc;
			break;
		default: // Parent case ... default
			message = "This is the parent";
			n = np;
			ns = tp;
			break;
	}

	// Print the messages and sleep for needed time
	for (; n > 0; n--) {
		puts(message);
		sleep(ns);
	}
	// printf("fork program end \n");
	exit(0);
}
// Error Function
void err_sys(char *str) {
        printf("%s\n", str);
        exit(1);
}
// Convertion function - string to integer
int myAtoi(char *str) {
        int result = 0;
	// Skips if negative so that arguement is absolute valued
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
