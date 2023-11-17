// Kyle Tranfaglia
// COSC350 - Lab08
// Last Updated 11/07/23
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_THREADS 2

// Prototypes
void *factorial(void*);
void *sum(void*);

int main(int argc, char *argv[]) {
	// Argument Check
	if (argc != 2) {
		perror("Invalid number of arguments ... must provide one argument");
		exit(1);
	}
	// Create 2 threads
	pthread_t threads[NUM_THREADS];
	// Create first thread with sum function with error check
	if (pthread_create(&threads[0], NULL, sum, (void*)argv[1]) != 0) {
		printf("pthread Error");
		exit(2);
	}
	// Create second thread with factorial function with error check
	if (pthread_create(&threads[1], NULL, factorial, (void*)argv[1]) != 0) {
		printf("pthread Error");
		exit(3);
	}
	pthread_exit(NULL); // Exit the thread
	exit(0);
}

// Factorial function
void *factorial(void *arg) {
	// Sets result variable for a calculation and converts string argument to an integer for calculations
        int result = 1, number = atoi(arg);
        // Loop to compute factorial
        for (int i = 2; i <= number; i++) {
                result *= i;
	}
        printf("Factorial: %d\n", result); // Print factorial to terminal
        pthread_exit(NULL); // Exit the thread
}

// Sum function
void *sum(void *arg) {
        // Set result variable for a calculation and converts string argument to an integer for calculations
        int result = 0, number = atoi(arg);
        // Loop to compute sum
        for (int i = 1; i <= number; i++) {
                result += i;
	}
        printf("Sum: %d\n", result); // Print sum to terminal
        pthread_exit(NULL); // Exit the thread
}
