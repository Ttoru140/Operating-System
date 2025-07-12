// Write a C program to show how two related processes can communicate with
// each other by a named pipe.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    int fd;
    char *fifo = "myfifo";  // 1. FIFO file name
    char message[] = "Hello from Parent!";
    char buffer[100];

    // 2. Create the FIFO (named pipe)
    mkfifo(fifo, 0666);

    // 3. Create a child process
    pid_t pid = fork();

    if (pid > 0) {
        // 4. Parent process block

        // 5. Open FIFO for writing
        fd = open(fifo, O_WRONLY);

        // 6. Write message to FIFO
        write(fd, message, strlen(message) + 1);

        printf("Parent: Message sent.\n");

        close(fd);  // 7. Close the pipe
    }
    else if (pid == 0) {
        // 8. Child process block

        // 9. Open FIFO for reading
        fd = open(fifo, O_RDONLY);

read(fd, buffer, sizeof(buffer));

        printf("Child: Received message: %s\n", buffer);

        close(fd);  // 11. Close the pipe
    }

    // 12. Remove the FIFO file
    unlink(fifo);

    return 0;
}
