// Write a C program to create a main process named ‘parent_process’ having
// ‘n’ child processes without any grandchildren processes. Child Processes’
// names are child_1, child_2, child_3,......., child_n. Trace the position in the
// process tree. Number of child processes (n) and name of child processes will
// be given in the CLI of Linux based systems.
// Example:
// $ ./parent_process 3 child_1 child_2 child_3

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

// int main(int argc, char *argv[]) {
//     printf("Parent (PID %d) started here \n", getpid());
//     fflush(stdout);

//     int n = atoi(argv[1]);

//     for (int i = 0; i < n; i++) {
//         pid_t pid = fork();

//         if (pid == 0) {
//             printf("\nChild name : %s , Child ID : %d, Parent ID : %d \n", argv[i + 2], getpid(), getppid());
//             fflush(stdout);  //prevent from bufffering
//             sleep(20);
//             exit(EXIT_SUCCESS);
//         }
//     }

//     for (int i = 0; i < n; i++) {
//         wait(NULL);
//     }

//     return 0;
// }

 







int main(int argc, char *argv[]){
    printf("parent pid:%d\n",getpid());
    fflush(stdout);
    int n = atoi(argv[1]);
    for(int i=0;i<n;i++){
        pid_t  pid = fork();
        if(pid == 0){
            printf("argument: %s  child pid :%d  parent pid: %d\n", argv[i+2], getpid(), getppid());
            sleep(5);
            fflush(stdout);
            exit(EXIT_SUCCESS);
        }
    }
   
    for(int i =0; i<n;i++){
        wait(NULL);
    }
    return 0;
}
