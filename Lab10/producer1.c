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
	int dataSize = 5, randNum =0;
	struct sharedMemory *sharedMem = (struct sharedMemory *)shmat(memoryID, (void *)0, 0);

	sharedMem->in = sharedMem->out = 0;
	for (int i = 0; i < 5; i++) {
		sharedMem->array[i] = 0;
	}

	while (1) {
		while ((sharedMem->in + 1) % dataSize == sharedMem->out) {
                        printf("Buffer is full - Producer is waiting\n");
                        sleep(1);
                }
		randNum = rand() % 10 + 1;

		sharedMem->array[sharedMem->in] = randNum;
		sharedMem->in = (sharedMem->in + 1) % dataSize;

		printf("Produced: %d\n", randNum);
		printf("[");

		for (int i = 0; i < dataSize; i++) {
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
