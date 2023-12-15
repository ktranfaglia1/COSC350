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
};

int main() {
	// Variables - key values for semaphore and shared memeory segments
	key_t mutex, shmem;
	const int MUTEX = 0, FULL = 1, EMPTY = 2, DATASIZE = 5;;
	int mutexId, memId;
	union semun mutSemun, emptySemun, fullSemun;

	// Generate keys for the semaphore and shared memory segments and error check
	if ((mutex = ftok(".", 'M')) == -1 || (shmem = ftok(".", 'S')) == -1) {
		perror("ftok Error");
		exit(1);
	}
	// Create or get the semaphore and shared memory segments and error check
	if ((mutexId = semget(mutex, 3, 0666 | IPC_CREAT)) == -1) {
		perror("semget Error");
		exit(1);
	}
	// Create or get ID for shared memory
	if ((memId = shmget(shmem, sizeof(struct sharedMemory), 0666 | IPC_CREAT)) == -1) {
        perror("shmget Error");
		exit(1);
	}
	struct sharedMemory *memory = (struct sharedMemory *)shmat(memId, (void *)0, 0); // Attach the shared memory segment to the process's address space
	// Check for memory attachment fail
	if (memory == (struct sharedMemory *)(-1)) {
		perror("Memory creation fail");
		exit(-1);
	}
	// Initialize the variables for semaphore and shared memory
	mutSemun.val = 1;
	emptySemun.val = DATASIZE;
	fullSemun.val = 0;
	// Set initial values for semaphores using semctl and error check
	if (semctl(mutexId, MUTEX, SETVAL, mutSemun) == -1 || semctl(mutexId, FULL, SETVAL, fullSemun) == -1 || semctl(mutexId, EMPTY, SETVAL, emptySemun) == -1) {
		perror("semctl Error");
		exit(1);
	}
	shmdt(memory); // Detach the shared memory segment from the process's address space
	return 0;
}