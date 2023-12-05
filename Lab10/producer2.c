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

void down(int semid) {
	struct sembuf buf = {0, -1, 0};
	semop(semid, &buf, 1);
}

void up(int semid) {
	struct sembuf buf = {0, 1, 0};
	semop(semid, &buf, 1);
}

struct sharedMemory {
	int array[5];
	int in;
	int out;
};

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
int main() {
	key_t mutex, empty, full, shMem;
	int mutexId, emptyId, fullId, shMemId, consumedData, dataSize = 5;

	if ((mutex = ftok(".", 'M')) == -1 || (empty = ftok(".", 'E')) == -1 || (full = ftok(".", 'F')) == -1 || (shMem = ftok(".", 'S')) == -1) {
		perror("ftok Error");
		exit(1);
	}

	if ((mutexId = semget(mutex, 1, 0666)) == -1 || (emptyId = semget(empty, 1, 0666)) == -1 || (fullId = semget(full, 1, 0666)) == -1 || (shMemId = shmget(shMem, sizeof(struct sharedMemory), 0666)) == -1) {
		perror("semget Error");
		exit(1);
	}
	struct sharedMemory *memory = (struct sharedMemory *)shmat(shMemId, (void *)0, 0);
	for (int i = 0; i < 5; i++) {
                memory->array[i] = 0;
        }

	while (1) {
		down(fullId);
		down(mutexId);

		consumedData = rand() % 10 + 1;

		memory->array[memory->out] = consumedData;
		memory->out = (memory->out + 1) % dataSize;

		up(mutexId);
		up(emptyId);

		printf("Produced: %d\n", consumedData);
		outputMemory(memory);
		sleep(1);
	}
	return 0;
}
