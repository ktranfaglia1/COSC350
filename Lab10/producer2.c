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
	int in;
	int out;
};

// Function prototypes
void down(int semid);
void up(int semid);
void outputMemory(struct sharedMemory* memory);

int main() {
	// Variables - key values for semaphore and shared memeory segments
	key_t mutex, empty, full, shMem;
	int mutexId, emptyId, fullId, shMemId, consumedData, dataSize = 5;
	// Generate keys for the semaphore and shared memory segments
	if ((mutex = ftok(".", 'M')) == -1 || (empty = ftok(".", 'E')) == -1 || (full = ftok(".", 'F')) == -1 || (shMem = ftok(".", 'S')) == -1) {
		perror("ftok Error");
		exit(1);
	}
    // Get identifiers for the existing semaphore and shared memory segments
	if ((mutexId = semget(mutex, 1, 0666)) == -1 || (emptyId = semget(empty, 1, 0666)) == -1 || (fullId = semget(full, 1, 0666)) == -1 || (shMemId = shmget(shMem, sizeof(struct sharedMemory), 0666)) == -1) {
		perror("semget Error");
		exit(1);
	}
	struct sharedMemory *memory = (struct sharedMemory *)shmat(shMemId, (void *)0, 0); // Attach the shared memory segment to the process's address space
	// Check for memory attachment fail
	if (memory == (struct sharedMemory *)(-1)) {
		perror("Memory creation fail");
		exit(-1);
	}
	// Infinite producer loop
	while (1) {
		// Perform semaphore operations for producing
		down(fullId);
		down(mutexId);
		consumedData = rand() % 10 + 1;  // Generate a random number (simulating produced data)
		// Write the produced data to the shared memory array
		memory->array[memory->out] = consumedData;
		memory->out = (memory->out + 1) % dataSize;
		// Release the semaphore
		up(mutexId);
		up(emptyId);
	    // Display produced data and the current state of shared memory
		printf("Produced: %d\n", consumedData);
		outputMemory(memory);
		sleep(1);
	}
	shmdt(memory); // Detach the shared memory segment from the process's address space
	return 0;
}
// Function to perform a semaphore down operation
void down(int semid) {
	struct sembuf buf = {0, -1, 0};
	semop(semid, &buf, 1);
}
// Function to perform a semaphore up operation
void up(int semid) {
	struct sembuf buf = {0, 1, 0};
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