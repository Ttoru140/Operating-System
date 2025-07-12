// Write a C program to show how two related processes can communicate with
// each other by a message queue.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>

// Define message structure
struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key = ftok("progfile", 65);              // Generate unique key
    int msgid = msgget(key, 0666 | IPC_CREAT);     // Create message queue

    pid_t pid = fork();                            // Create child process

    if (pid > 0) {
        // Parent sends message
        struct msg_buffer msg = {1, "Hello from Parent!"};
        msgsnd(msgid, &msg, sizeof(msg.msg_text), 0);
        printf("Parent: Message sent.\n");
        wait(NULL);                                // Wait for child
    } else {
        // Child receives message
        struct msg_buffer msg;
        sleep(1);                                   // Ensure parent sends first
        msgrcv(msgid, &msg, sizeof(msg.msg_text), 1, 0);
        printf("Child: Received message: %s\n", msg.msg_text);
        msgctl(msgid, IPC_RMID, NULL);              // Remove message queue
    }

    return 0;
}
