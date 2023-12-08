// Kyle Tranfaglia
// COSC350 - Lab10
// Last Updated 12/04/23
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

// Structure to represent the shared memory layout
struct sharedMemory {
	int array[5];
};

// Function prototypes
void down(int, int);
void up(int, int);
void outputMemory(struct sharedMemory*);

int main() {
	// Variables - key values for semaphore and shared memeory segments
	key_t mutex, shmem;
	const int MUTEX = 0, FULL = 1, EMPTY = 2, DATASIZE = 5;;
	int mutexId, memId, consumedData;
	// Generate keys for the semaphore and shared memory segments
	if ((mutex = ftok(".", 'M')) == -1 || (shmem = ftok(".", 'S')) == -1) {
		perror("ftok Error");
		exit(1);
	}
    // Get identifiers for the existing semaphore and shared memory segments
	if ((mutexId = semget(mutex, 3, 0666)) == -1 || (memId = shmget(shmem, sizeof(struct sharedMemory), 0666)) == -1) {
		perror("semget Error");
		exit(1);
	}
	struct sharedMemory *memory = (struct sharedMemory *)shmat(memId, (void *)0, 0); // Attach the shared memory segment to the process's address space
	// Check for memory attachment fail
	if (memory == (struct sharedMemory *)(-1)) {
		perror("Memory creation fail");
		exit(-1);
	}
	// Infinite consumer loop
	while (1) {
		// Perform semaphore operations for producing
		down(mutexId, FULL);
		down(mutexId, MUTEX);
		consumedData = memory->array[semctl(mutexId, FULL, GETVAL)];
		memory->array[semctl(mutexId, FULL, GETVAL)] = 0;// Remove the produced data from the shared memory array
	    // Display produced data and the current state of shared memory
		outputMemory(memory);
		printf("Consumed: %d\n", consumedData);
		// Release the semaphore
		up(mutexId, MUTEX);
		up(mutexId, EMPTY);
		sleep(1);
	}
	return 0;
}
// Function to perform a semaphore down operation
void down(int semid, int index) {
	struct sembuf buf = {index, -1, 0};
	semop(semid, &buf, 1);
}
// Function to perform a semaphore down operation
void up(int semid, int index) {
	struct sembuf buf = {index, 1, 0};
	semop(semid, &buf, 1);
}
// Function to output the contents of the shared memory array as a list
void outputMemory(struct sharedMemory* memory) {
	printf("[");
	for (int i = 0; i < 5; i++) {
		printf("%d", memory->array[i]);
		if (i < 4) {
			printf(", ");
		}
	}
	printf("]\n");
}