// Kyle Tranfaglia
// COSC350 - Lab10
// Last Updated 12/04/23
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// Structure to represent the shared memory layout
struct sharedMemory {
	int array[5];
	int in;
	int out;
};

int main() {
	key_t key = ftok(".", 'A'); // Generate a key for the shared memory segment using the current directory and 'A'
	// Check for key fail
	if (key == -1) {
		perror("Key creation fail");
		exit(-1);
	}
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
	memory->in = memory->out = 0; // Initialize in and out
	// Initialize the list of data
	for (int i = 0; i < 5; i++) {
		memory->array[i] = 0;
	}
	shmdt(memory); // Detach the shared memory segment from the process's address space
	return 0;
}