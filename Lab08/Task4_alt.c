#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 256

int main(void)
{
	int n, fd[2];
	char in[MAXLINE];
	pid_t pid;
	//Check for pipe fail
	if (pipe(fd) < 0)
	{
		perror("pipe error\n");
		exit(1);
	}
	pid = fork();
	//fork error
	if(pid < 0)
	{
		perror("fork error\n");
		exit(1);
	}
	//child process
	if(pid == 0)
	{
		//close write
		close(fd[1]);
		int int1, int2;
		//Read in from parent
		while((n=read(fd[0], in, MAXLINE))>0)
		{
			//Check for integer
			if(sscanf(in, "%d%d", &int1, &int2)==2)
			{
				//Do the sum and store in in
				sprintf(in, "Sum: %d\n", int1+int2);
				//Get size of in for write system call
				n = strlen(in);
				//Write the string
				if(write(0, in, n) != n)
				{
					printf("write error");
					exit(1);
				}
			}
			//If less than or more than 2 int
			else
			{
				if(write(0, "invalid args\n", 13) != 13)
				{
					printf("write error");
					exit(1);
				}

			}
		}
	}
	//Parent process
	else
	{
		//close read
		close(fd[0]);
		int i;
		printf("intput 2 integer\n");
		//Get from keyboard
		while((fgets(in, MAXLINE, stdin) != NULL))
		{
			//Get string length
			n=strlen(in);
			//pipe to the child
			if(write(fd[1], in, n) != n)
			{
				printf("Write error");
				exit(1);
			}		
		}
	}
	exit(0);
}
