//write a c program to create a main preocess name tintin and 2 child process without grandchild name of them are A and B

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("Main process name: tintin (PID: %d)\n", getpid());

    pid_t pidA = fork();  // First child A

    if (pidA < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pidA == 0) {
        // Child A
        printf("Child Process A created (PID: %d, PPID: %d)\n", getpid(), getppid());
        exit(0);
    }

    pid_t pidB = fork();  // Second child B

    if (pidB < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pidB == 0) {
        // Child B
        printf("Child Process B created (PID: %d, PPID: %d)\n", getpid(), getppid());
        exit(0);
    }

    // Tintin waits for both children to finish
    wait(NULL);
    wait(NULL);

    printf("Tintin (PID: %d) ends after children finish.\n", getpid());

    return 0;
}
