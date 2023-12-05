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

// Structure to represent a message with an array and an ID
struct message {
    char msgArray[256];
    long msgID;
};

int main() {
    key_t key = ftok("msgQsnd.c", 'A'); // Generate a key for the message queue using the file "msgQsnd.c" and character 'A'
    int msgid = msgget(key, 0644); // Access the existing message queue with the specified key and permission flags

    // Check for message queue open fail
    if (msgid < 0) {
        perror("Queue Open Failed\n");
        exit (1);
    }
    // Create a message structure and initialize the ID
    struct message msg;
    msg.msgID = 1;
    int num1 = 0, num2 = 0;
    // Infinite loop to receive and process messages
    while (1) {
        // Receive a message from the message queue and error check
        if (msgrcv(msgid, (struct message *)&msg, sizeof(msg), 0, 0) == -1) {
            perror("Message recieve failed");
            exit(1);
        }
        // Check if the message contains two integers for addition
        if (sscanf(msg.msgArray, "%d %d", &num1, &num2) == 2) {
            printf("The Sum is : %d \n", num1 + num2);
        }
        // Check if the message indicates communication termination
        else if (strcmp(msg.msgArray, "COMMUNICATION TERMINATED") == 0) {
            printf("Communication has been terminated ... Exiting\n");
            break;
        }
        // Handle invalid input
        else {
            printf("Invalid input!\n");
        }
    }
    msgctl(msgid, IPC_RMID, NULL); // Remove the message queue when the loop ends
    return 0;
}