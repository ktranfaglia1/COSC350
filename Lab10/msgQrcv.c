// Kyle Tranfaglia
// COSC350 - Lab10
// Last Updated 12/04/23
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/msg.h>

struct message {
    char msgArray[256];
    long msgID;
};

int main() {
    key_t key = ftok("msgQsnd.c", 'A');

    int msgid = msgget(key, 0644);

    if (msgid < 0)
    {
        perror("Queue Open Failed\n");
        exit (1);
    }

    struct message msg;
    msg.msgID = 1;
    int num1 = 0, num2 = 0;

    while (msgrcv(msgid, (struct message *)&msg, sizeof(msg), 0, 0) > 0) {
	if (sscanf(msg.msgArray, "%d %d", &num1, &num2) == 2) {
		printf("The Sum is : %d \n", num1 + num2);
	}
	else {
		printf("Invalid input!\n");
	}
    }
}
