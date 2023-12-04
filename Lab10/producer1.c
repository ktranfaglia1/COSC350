// Kyle Tranfaglia
// COSC350 - Lab10
// Last Updated 12/04/23
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

struct sharedMemory {
	int array[5];
	int in;
	int out;
};

int main() {
	key_t key = ftok(".", 'A');
	int memoryID = shmget(key, sizeof(struct sharedMemory), 0666);
	int dataSize = 5;
	struct sharedMemory *sharedMem = (struct sharedMemory *)shmat(memoryID, (void *)0, 0);

	while (1) {
		int randNum = rand() % 10 + 1;

		while ((sharedMem->in + 1) % dataSize == sharedMem->out) {
			printf("Full Buffer Waiting ...\n");
			sleep(1);
		}

		sharedMem->array[sharedMem->in] = randNum;
		sharedMem->in = (sharedMem->in + 1) % dataSize;

		printf("Produced:\n");

		printf("[");
		for (int i = 0; i < dataSize; ++i) {
			printf("%d", sharedMem->array[i]);
			if (i < dataSize - 1) {
				printf(", ");
			}
		}

		printf("]\n");
		sleep(1);
	}
	shmdt(sharedMem);
	return 0;
}
