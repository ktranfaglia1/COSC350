// Kyle Tranfaglia
// COSC350 - Lab09
// Last Updated 11/20/23
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <errno.h>
#include "header.h"

int main(int argc, char **argv) {
	int shmid;
	struct Memory *shm;
	key_t key = ftok(".",'x'); // Get key value
	// Get shared memory segement - returns the shared memory identifier associated with key and error checks
	if ((shmid = shmget(key, sizeof(struct Memory), 0)) < 0) {
		perror("shmget error \n");
		exit (1);
	}
	shm = (struct Memory *) shmat(shmid, NULL, 0); // Attach to shared memory segment associated with shmid
	// Error check shmat
	if ((long) shm == -1) {
		perror("shmat error\n");
		exit(1);
	}
	// Read from the shared memory until signaled to stop
	while (shm->gostop == GO) {
		// Loop to run and wait to sum numbers until two are given (status is filled)
		while (shm->status != FILLED) {
			// Stop running if data read is set to stop
			if (shm->gostop == STOP) {
				break;
			}
		}
		printf("Sum of the two integer: %d\n", shm->data.int1 + shm->data.int2); // Calculate and print sum
		shm->status = TAKEN;
	}
	shmdt((void*)shm); // Detach shared memory segment
	return 0;
}
