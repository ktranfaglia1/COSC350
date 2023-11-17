// Kyle Tranfaglia
// COSC350 - Lab07
// Last Updated 10/30/23
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

// Prototype
void ouch(int);

int main() {
	(void) signal(SIGINT, ouch); // Sets signal to call ouch function
	// Always run
	while(1) {
		printf("Hello World!\n");
		sleep(1);
	}
}
// Fucntion to handle signals
void ouch(int sig) {
        printf("\nOUCH! I got signal %d\n", sig); // Prints that signal was recieved and print signal number
        (void) signal(SIGINT, SIG_DFL); // Again, sets how to process signal, this time setting it flag an exit
}
