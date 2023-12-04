// Kyle Tranfaglia
// COSC350 - Lab10
// Last Updated 12/04/23
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
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
	struct sharedMemory *memory = (struct sharedMemory *)shmat(memoryID, (void *)0, 0);

	while (1) {
		while (memory->in == memory->out) {
			printf("Buffer is empty - Consumer is waiting\n");
			sleep(1);
		}
		int consumedData = memory->array[memory->out];
		memory->array[memory->out] = 0;
		memory->out = (memory->out + 1) % dataSize;

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
	shmdt(memory);
	return 0;
}
