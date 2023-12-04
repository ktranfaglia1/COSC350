// Kyle Tranfaglia
// COSC350 - Lab10
// Last Updated 12/04/23
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<errno.h>
#include <sys/msg.h>

struct message {
    char msgArray[256];
    long msgID;
};

int main() {
    key_t key = ftok("msgQsnd.c", 'A');

    if (key < 0){
        perror("Key Making Failed \n");
        exit (1);
    }

    int msgid = msgget(key, 0644 | IPC_CREAT);

    if (msgid < 0) {
        perror("Queue Open Failed \n");
        exit (1);
    }

    struct message msg;
    msg.msgID = 1;

    printf("Input Two Integer Values\n");
    while (fgets(msg.msgArray, sizeof(msg.msgArray), stdin) != NULL) {
	if (msgsnd(msgid, (struct message *)&msg, sizeof(msg), 0) == -1) {
		perror("MESSAGE FAILED TO SEND");
	}
        printf("Input Two Integer Values\n");
    }
    msgctl(msgid, IPC_RMID, NULL);
    exit(0);
}
