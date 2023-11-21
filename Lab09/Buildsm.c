// Kyle Tranfaglia
// COSC350 - Lab09
// Last Updated 11/20/23
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <errno.h>
#include "header.h"

int main(int argc, char **argv) {
	// Variables
	int shmid;
	struct Memory *shm;
	key_t key = ftok(".", 'x'); // Creates a key value
	// Get shared memory segement - returns the shared memory identifier associated with key and error checks
	if ((shmid = shmget(key, sizeof(struct Memory), IPC_CREAT | 0666)) < 0) {
		perror("shmget error\n");
		exit(1);
	}
	shm = (struct Memory *) shmat(shmid, NULL, 0); // Attach to shared memory segment associated with shmid
	// Error check shmat function
	if ((long)shm == -1) {
		perror("shmat error \n");
		exit(1);
	}
	shm->status = NOT_READY; // Set status to not ready
	shm->gostop = GO; // Set data send identifier to go
	return 0;
}
