// Kyle Tranfaglia
// COSC350 - Lab07
// Last Updated 10/30/21
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// Prototype
void doNothing(int);

int main() {
	// Sig set variables
	sigset_t addSet, originalSet;

	sigemptyset(&addSet); // Clears the set space ... should be redundant
	sigaddset(&addSet, SIGINT); // Adds signal to set
	sigaddset(&addSet, SIGQUIT); // Adds signal to set
	// Sets signal mask with error check
	if (sigprocmask(SIG_BLOCK, &addSet, &originalSet) == -1) {
		perror("Sigprocmask error");
		exit(1);
	}
	// Loops to print 1 through 5
	for (int i = 1; i <= 5; i++) {
		printf("%d\n", i);
		sleep(1);
	}
	signal(SIGQUIT, &doNothing); // Catch the signal and do nothing ... no quitting allowed

	sigdelset(&addSet, SIGINT); // Removes signal from set
	// Unblocks signals in set by seting the signal mask with addset with error check ... ctrl \ now terminates program
	if (sigprocmask(SIG_UNBLOCK, &addSet, &originalSet) == -1) {
                perror("Sigprocmask error");
                exit(2);
        }

	signal(SIGQUIT, SIG_DFL); // Catches signals from the queue
	// Loops to print 1 through 5
	for (int i = 1; i <= 5; i++) {
		printf("%d\n", i);
		sleep(1);
	}
	// Resets the mask for the original set to its default with error check
	if (sigprocmask(SIG_SETMASK, &originalSet, NULL) == -1) {
		perror("Sigprocmask error");
                exit(3);
        }
	return 0;
}
// Function to do nothing ... dismisses signal calls
void doNothing(int sig) {
	return;
}
