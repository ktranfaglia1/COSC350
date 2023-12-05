// Kyle Tranfaglia
// COSC350 - Lab10
// Last Updated 12/04/23
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

// Union for semaphore operations
union semun {
	int val; // for SETVAL
	struct semid_ds *buf; // for IPC_STAT and IPC_SET
	unsigned short *array; // for GETALL and SETALL
};
// Structure to represent the shared memory layout
struct sharedMemory {
	int array[5];
	int in;
	int out;
};

int main() {
	// Variables - key values for semaphore and shared memeory segments
	key_t mutex, empty, full, shmem;
	int mutexId, emptyId, fullId, memId, dataSize = 5;
	union semun mutSemun, emptySemun, fullSemun;

	// Generate keys for the semaphore and shared memory segments and error check
	if ((mutex = ftok(".", 'M')) == -1 || (empty = ftok(".", 'E')) == -1 || (full = ftok(".", 'F')) == -1 || (shmem = ftok(".", 'S')) == -1) {
		perror("ftok Error");
		exit(1);
	}
	// Create or get the semaphore and shared memory segments and error check
	if ((mutexId = semget(mutex, 1, 0666 | IPC_CREAT)) == -1 || (emptyId = semget(empty, 1, 0666 | IPC_CREAT)) == -1 || (fullId = semget(full, 1, 0666 | IPC_CREAT)) == -1 || (memId = shmget(shmem, sizeof(struct sharedMemory), 0666 | IPC_CREAT)) == -1) {
		perror("semget Error");
		exit(1);
	}
	struct sharedMemory *memory = (struct sharedMemory *)shmat(memId, (void *)0, 0); // Attach the shared memory segment to the process's address space

	// Initialize the variables for semaphore and shared memory
	memory->in = memory->out = 0;
	mutSemun.val = 1;
	emptySemun.val = 0;
	fullSemun.val = dataSize;

	shmdt(memory); // Detach the shared memory segment from the process's address space
	
	// Set initial values for semaphores using semctl and error check
	if (semctl(mutexId, 0, SETVAL, mutSemun) == -1 || semctl(emptyId, 0, SETVAL, emptySemun) == -1 || semctl(fullId, 0, SETVAL, fullSemun) == -1) {
		perror("semctl Error");
		exit(1);
	}
	return 0;
}