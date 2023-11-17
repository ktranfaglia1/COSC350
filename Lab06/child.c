// Kyle Tranfaglia
// COSC350 - Lab06
// Last updated  10/23/23
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	char *message = argv[0]; // Gets message
	// Sets number and sleep arguements
	int nc = atoi(argv[1]), tc = atoi(argv[2]);
	// Loop to sleep and display message for count
 	for (int i = 0; i < nc; i++) {
  		puts(message);
   		sleep(tc);
	}
	exit(37);
}
