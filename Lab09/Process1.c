// Kyle Tranfaglia
// COSC350 - Lab09
// Last Updated 11/20/23
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <errno.h>
#include "header.h"

int main(int argc, char**argv) {
	// Variables
	int shmid, num1, num2;
	char buffer[BUFSIZ+1];
	struct Memory *shm;
	key_t key = ftok(".", 'x'); // Get key value
	// Get shared memory segement - returns the shared memory identifier associated with key and error checks
	if ((shmid = shmget(key, sizeof(struct Memory), 0)) < 0 ) {
		perror("shmget error \n");
		exit(1);
	}
	shm = (struct Memory *) shmat(shmid, NULL, 0); // Attach to shared memory segment associated with shmid
	// Error check shmat function
	if ((long)shm == -1) {
		perror("shmat error \n");
		exit(1);
	}
	shm->gostop = GO; // Set data send identifier to go
	shm->status = NOT_READY; // Set status identifier to not ready

	memset(buffer, '\0', sizeof(buffer)); // Set end of string character to end of buffer
	printf("Enter two integers: \n");
	// Run as long as there is something to be read
	while(read(0, buffer, BUFSIZ) > 0){
		// Check if buffer contains two integers, if so, set shared memory integers and continue asking for integers
		if (sscanf(buffer, "%d%d", &num1, &num2) == 2) {
			shm->data.int1 = num1;
			shm->data.int2 = num2;
			while(shm->status != TAKEN);
			printf("Enter two integers: \n");
		}
		else {
			printf("Invliad integers\n Enter two integers:\n");
		}
	}
	shm->gostop = STOP; // Set data send identifier to stop
	shmdt((void *) shm); // Detach shared memory segment
	return 0;
}
