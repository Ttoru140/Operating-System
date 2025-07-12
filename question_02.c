//Write a C program to create an orphan process. 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Error handling
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        sleep(5);  // Sleep to ensure parent exits first
        printf("Child process (PID: %d), Parent PID after becoming orphan: %d\n", getpid(), getppid());
    } else {
        // Parent process
        printf("Parent process (PID: %d) is exiting...\n", getpid());
        exit(0);
    }

    return 0;
}





