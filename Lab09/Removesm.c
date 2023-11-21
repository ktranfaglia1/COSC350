// Kyle Tranfaglia
// COSC350 - Lab09
// Last Updated 11/20/23
#include <stdio.h>
#include <sys/shm.h>
#include <errno.h>
#include <stdlib.h>
#include "header.h"

int main(int argc, char ** argv) {
	// Variables
	int shmid;
	struct Memory shm;
	key_t key = ftok(".", 'x');
	// Get shared memory segement - returns the shared memory identifier associated with key and error checks
	if ((shmid = shmget(key, sizeof(struct Memory), 0)) < 0) {
		perror("shmget error \n");
		exit(1);
	}
	shmctl(shmid, IPC_RMID, NULL); // Performs the control operation on shared memory segment whose identifier is given in shmid
	return 0;
}
