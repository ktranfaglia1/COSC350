// Kyle Tranfaglia
// COSC350 - Lab08
// Last Updated 11/07/23
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_THREADS 4

int *globalArray; // Global array to be allocated in thread1
int counter = 0; // Counter to keep track of array size

// Thread Prototypes
void *Thread1(void*);
void *Thread2(void*);
void *Thread3(void*);
void *Thread4(void*);

int main() {
	// Variables
	pthread_t threads[NUM_THREADS]; // Array of threads
	int thread = 0; // Thread descriptor for thread cration
	void *wait; // Wait void pointer

	// Create thread 1 and error check
	thread = pthread_create(&threads[0], NULL, Thread1, NULL);
	if (thread != 0) {
		printf("pthread error: %d\n", thread);
		exit(1);
	}
	// Wait for thread 1 to finish and error check
	thread = pthread_join(threads[0], &wait);
	if (thread != 0) {
		printf("pthread error: %d\n", thread);
                exit(1);
	}
	// Create thread 2 and error check
	thread = pthread_create(&threads[1], NULL, Thread2, NULL);
	if (thread != 0) {
		printf("pthread error: %d\n", thread);
                exit(1);
	}
	// Create thread 3 and error check
	thread = pthread_create(&threads[2], NULL, Thread3, NULL);
	if (thread != 0) {
		printf("pthread error: %d\n", thread);
		exit(1);
	}
	// Wait for thread 2 to finish and error check
	thread = pthread_join(threads[1], &wait);
	if (thread != 0) {
		printf("pthread error: %d\n", thread);
		exit(1);
	}
	// Wait for thread 3 to finish and error check
	thread = pthread_join(threads[2], &wait);
	if (thread != 0) {
		printf("pthread error: %d\n", thread);
		exit(1);
	}
	// Create thread 4 and error check
	thread = pthread_create(&threads[3], NULL, Thread4, NULL);
	if (thread != 0) {
		printf("pthread error: %d\n", thread);
		exit(1);
	}
	// Wait for thread 4 to finish and error check
	thread = pthread_join(threads[3], &wait);
	if (thread != 0) {
		printf("pthread error: %d\n", thread);
		exit(1);
	}
	pthread_exit(NULL); // Exits the threads
	free(globalArray); // Free dynamically allocated global array
	exit (0);
}
// Thread 1 process
void *Thread1(void *arg) {
	globalArray = (int*)malloc(20*sizeof(int)); // Allocates the memory to hold 20 integers for the global array for the threads
	char buffer; // Buffer variable
	// Get test scores from keyboard (Until 20 scores or a non-integer value)
	printf("Enter a test score and press enter for 20 test scores or type a non-integer input to stop input\n");
	while ((counter < 20) && (scanf("%d", &buffer))) {
		globalArray[counter++] = buffer;
	}
	printf("No Longer accepting scores\n"); // Tells user that no more scores will be read
	pthread_exit(NULL); // Exits thread
}
// Thread 2 process
void *Thread2(void *arg) {
	// Variables
	int sum = 0;
	double median = 0.0;
	// Find Sum of data in array
	for (int i = 0; i < counter; i++) {
		sum += globalArray[i];
	}
	// Get and print the average using the sum and array size
	printf("Average: %.2f\n", sum / (float)counter);
	// Temp array to hold a copy of the array for sorting
	int *temp = (int*) malloc(counter*sizeof(int));
	for (int i = 0; i < counter; i++) {
		temp[i] = globalArray[i];
	}
	// Bubble sort the temp array
	for (int i = 0; i < counter; i++) {
		for (int j = 0; j < counter - i - 1; j++) {
			if (temp[j] > temp[j + 1]) {
				int hold = temp[j];
				temp[j] = temp[j + 1];
				temp[j + 1] = hold;
			}
		}
	}
	// If there is even number of scores, calculate the average of middle two scores
	if (counter % 2 == 0) {
		median = (temp[counter / 2 - 1] + temp[counter / 2]) / 2.00;
	}
	// For an odd number, get the middle score
	else {
		median = temp[(counter / 2)];
	}
	printf("Median: %.2f\n", median); // Print the median
	free(temp); // Free the dynamically allocated temp array
	pthread_exit(NULL); // Exits the thread
}
// Thread 3 process
void *Thread3(void *arg) {
	// Initialize min and max to first score
	int min = globalArray[0], max = globalArray[0];
	// Loop through array and update min and max if array at index is less than min or greater than max
	for (int i = 1; i < counter; i++) {
		if (min > globalArray[i]) {
			min = globalArray[i];
		}
		if (max < globalArray[i]) {
			max = globalArray[i];
		}
	}
	printf("Min: %d\nMax: %d\n", min, max); // Prints the min and the max values
	pthread_exit(NULL); // Exits the thread
}
// Thread 4 process
void *Thread4(void *arg) {
	// Set all the array scores to 0
	for (int i = 0; i < counter; i++) {
		globalArray[i] = 0;
		printf("%d ", globalArray[i]); // Print value after clear
	}
	printf("\n"); // Print newline for formatting
	pthread_exit(NULL); // Exit thread
}
