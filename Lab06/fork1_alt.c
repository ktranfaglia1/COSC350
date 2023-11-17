// fork1.c
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	//Need 4 argument
	if(argc != 5) {
		perror("Need 4 arguements!\n");
		exit(1);
	}
	//Convert the arguemnt into integer and initialize
	int Nc = atoi(argv[1]);
	int Np = atoi(argv[2]);
	int Tc = atoi(argv[3]);
	int Tp = atoi(argv[4]);
	//Hold pid variable
	pid_t pid;
	char *message;
	int n, s;
	printf("fork program starting\n");
	//Start fork
	pid = fork();
	switch(pid) {
		//fork fail case
		case -1:
			perror("fork failed");
			exit(1);
		//fork child
		case 0:
			message = "This is the child";
			n = Nc;
			s = Tc;
			break;
		//fork parent
		default:
			message = "This is the parent";
			n = Np;
			s = Tp;
			break;
	}
	//Prints the message and sleep
	for(; n > 0; n--){
		puts(message);
		sleep(s);
	}
	exit(0);
}
