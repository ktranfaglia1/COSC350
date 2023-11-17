// Kyle Tranfaglia
// COSC350 - Lab07
// Last Updated 10/30/23
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

// Prototype
void ouch(int);

int main() {
	struct sigaction signal; // Signal structure

	signal.sa_handler = ouch; // Sets signal handler to ouch function with use of sigaction
	sigemptyset(&signal.sa_mask); // Initialises the signal set pointed to by set, such that all signals defined in this document are excluded
	signal.sa_flags = SA_RESETHAND; // Sets flags ... or something like that

	sigaction(SIGINT, &signal, 0); // Sets sigaction to handle signial
	// Forever running loop
	while (1) {
		printf("Hello World!\n");
		sleep(1);
	}
}
// Function to handle the signal when sent and processed by sigaction
void ouch(int sig) {
        printf("\nOUCH! I got signal %d\n", sig);
}
