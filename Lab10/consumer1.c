// Kyle Tranfaglia
// COSC350 - Lab10
// Last Updated 12/04/23
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

// Structure to represent the shared memory layout
struct sharedMemory {
	int array[5];
	int in;
	int out;
};

int main() {
	// Variables
	key_t key = ftok(".", 'A'); // Generate a key for the shared memory segment using the current directory and 'A'
	int dataSize = 5;

	int memoryID = shmget(key, sizeof(struct sharedMemory), 0666 | IPC_CREAT); // Create a shared memory segment with the specified key and size
	// Check for shared memory creation fail
	if (memoryID == -1) {
		perror("ID Failed");
		exit(-1);
	}
	struct sharedMemory *memory = (struct sharedMemory *)shmat(memoryID, (void *)0, 0); // Attach the shared memory segment to the process's address space
	// Check for memory attachment fail
	if (memory == (struct sharedMemory *)(-1)) {
		perror("Memory creation fail");
		exit(-1);
	}
	// Infinite loop to consume data from the shared memory
	while (1) {
		// Wait until there is data to consume if buffer is empty
		while (memory->in == memory->out) {
			printf("Buffer is empty - Consumer is waiting\n");
			sleep(1);
		}
		// Consume data from the shared memory
		int consumedData = memory->array[memory->out];
		memory->array[memory->out] = 0;
		memory->out = (memory->out + 1) % dataSize;

		// Display consumed data and the current state of shared memory as an array list
		printf("Consumed: %d\n", consumedData);
		printf("Shared Memory Contents: [");
		for (int i = 0; i < dataSize; ++i) {
			printf("%d", memory->array[i]);
			if (i < dataSize - 1) {
				printf(", ");
			}
		}
		printf("]\n");
		sleep(1);
	}
	shmdt(memory); // Detach the shared memory segment from the process's address space
	return 0;
}