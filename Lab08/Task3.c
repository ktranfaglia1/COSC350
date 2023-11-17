// Kyle Tranfaglia
// COSC350 - Lab08
// Last Updated 11/07/23
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NUM_THREADS 2

// Clean-up Handler Prototype
void *Bye1 (void*);
void *Bye (void*);

// Thread Prototypes
void *Thread1(void*);
void *Thread2(void*);

int main() {
    pthread_t threads[NUM_THREADS]; // Array of threads
    // Create two threads
    pthread_create(&threads[0], NULL, Thread1,(void*)pthread_self());
    pthread_create(&threads[1], NULL, Thread2, (void*)threads[0]);
    // Set original thread to call Bye1 function upon termination
    pthread_cleanup_push(Bye1, NULL);
    // Loop to run forever and test if cancel requested
    while (1) {
	sleep(1);
        printf("In the original thread\n");
        pthread_testcancel();
    }
    pthread_cleanup_pop(0); // Pop cancel handler
    pthread_exit(0); // Exit thread
}
// First thread
void *Thread1(void *arg) {
    pthread_cleanup_push(Bye, arg); // Set cancel handler for thread
    // Loop to run forever and test if cancel requested
    while (1) {
	sleep(1);
        printf("In the first thread\n");
        pthread_testcancel();
    }
    pthread_cleanup_pop(0); // Pop cancel handler
    // pthread_exit(0); // Exit thread
}
// Second thread
void *Thread2(void *arg) {
    pthread_t tid = (pthread_t)arg; // Get thread id of Thread1 from parameter
    int count = 0; // Counter
    // Loop to run forever and request to cancel Thread1 after ten iterations
    while (1) {
	printf("In the second thread\n");
        sleep(1);
	count++;
	/// if ten iterations
        if (count == 10) {
            pthread_cancel(tid); // Request to cancel Thread1
           // pthread_exit(0); // Exit thread
        }
    }
}
// Function to handle cancel request for Thread1
void *Bye(void *arg) {
    pthread_t tid = (pthread_t)arg; // get thread id of original from parameter
    printf("Bye\n");
    pthread_cancel(tid); // Request to cancel Thread1
}
// Function to handle the requested cancel of the original thread
void *Bye1(void *arg) {
    printf("END OF THE PROGRAM\n");
    exit(0);
}
