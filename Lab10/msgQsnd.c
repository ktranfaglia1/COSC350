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
    // Check for key fail
    if (key < 0){
        perror("Key Making Failed \n");
        exit (1);
    }
    int msgid = msgget(key, 0644 | IPC_CREAT); // Open or create a message queue with the specified key and permission flags
    // Check for message queue opening/creation fail
    if (msgid < 0) {
        perror("Queue Open Failed \n");
        exit (1);
    }
    // Create a message structure and initialize the ID
    struct message msg;
    msg.msgID = 1;

    printf("Input Two Integer Values\n"); // Prompt the user to input two integer values
    // Loop to read input from the user and send messages
    while (fgets(msg.msgArray, sizeof(msg.msgArray), stdin) != NULL) {
        // Send the message to the message queue and error check
        if (msgsnd(msgid, (struct message *)&msg, sizeof(msg), 0) == -1) {
            perror("Message failed to send");
        }
        printf("Input Two Integer Values\n"); // Prompt the user to input two integer values again
    }
    // Send a special message to indicate the end of communication
    strcpy(msg.msgArray, "COMMUNICATION TERMINATED");
    if (msgsnd(msgid, (struct message *)&msg, sizeof(msg), 0) == -1) {
        perror("Message failed to send");
    }
    msgctl(msgid, IPC_RMID, NULL); // Remove the message queue when the loop ends
    return 0;
}
