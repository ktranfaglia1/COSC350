// Kyle Tranfaglia
// COSC350 - Lab10
// Last Updated 12/04/23
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

struct sharedMemory {
	int array[5];
	int in;
	int out;
};

int main() {
	key_t key = ftok(".", 'A');

	if (key == -1) {
		perror("Key creation fail");
		exit(-1);
	}

	int memoryID = shmget(key, sizeof(struct sharedMemory), 0666 | IPC_CREAT);

	if (memoryID == -1) {
		perror("ID Failed");
		exit(-1);
	}

	struct sharedMemory *memory = (struct sharedMemory *)shmat(memoryID, (void *)0, 0);

	if (memory == (struct sharedMemory *)(-1)) {
		perror("Memory creation fail");
		exit(-1);
	}
	memory->in = 0;
	memory->out = 0;
	shmdt(memory);
	return 0;
}

