// Write a C program to show how two unrelated processes can communicate
// with each other by a named pipe.




// reader.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>      // Correct header for O_RDONLY
#include <string.h> 
#include <sys/stat.h> // need for O_RDONLY
    // Needed if you want to use string functions

int main()
{
    int fd;
    char *fifo = "myfifo";
    char buffer[100];

    mkfifo(fifo, 0666);  // Create FIFO if it doesn't exist

    fd = open(fifo, O_RDONLY);  // Open FIFO for reading

    read(fd, buffer, sizeof(buffer));  // Read message into buffer

    printf("Received SMS: %s\n", buffer);

    close(fd);  // Always close the file descriptor

    return 0;
}





// writer.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>      // For O_WRONLY
#include <string.h> 
#include <sys/stat.h> // need for O_WRONLY
    // For strlen()

int main()
{
    int fd;
    char *fifo = "myfifo";
    char msg[] = "hello";

    mkfifo(fifo, 0666);  // Create named pipe if it doesn't exist

    fd = open(fifo, O_WRONLY);   // Open FIFO for writing

    write(fd, msg, strlen(msg)+1);  // Write message including null terminator

    printf("sent done\n");

    close(fd);   // Always close file descriptor

    return 0;
}



//  for output..
//  gcc q_09_reader.c -o q_09_reader
// gcc q_09_writer.c -o q_09_writer
// ./q_09_reader
// ./q_09_writer
