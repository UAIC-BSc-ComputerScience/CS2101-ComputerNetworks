#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>

#define FIFO_NAME "fifo"
#define OUTPUT_FILE "output.txt"

int prim(int);

int main(int argc, char** argv) {
    
    mkfifo(FIFO_NAME, S_IFIFO | 0666);
    

    int fdout = open(OUTPUT_FILE, O_RDWR | O_CREAT);


    pid_t pid = fork(); // -1


    if (pid == -1) {
        printf("Error fork();\n");
        exit(333);
    }

    if (pid != 0) {
    
        int fdr = open(FIFO_NAME, O_RDONLY); // -1

        close(0);

        if (dup(fdr) != 0) {
            printf("Error");
            exit(1);
        }
        
        close(fdr);

        close(1);

        if (dup(fdout) != 1) {
            printf("Error");
            exit(2);
        }

        close(fdout);

        wait(NULL);

        execlp("wc", "wc", NULL);

        printf("Error\n");
        exit(1);

    } else {

        int fdw = open(FIFO_NAME, O_WRONLY); // -1
        close(fdout);
        close(1);

        if (dup(fdw) != 1) {
            printf("Error");
            exit(3);
        }

        close(fdw);

        execlp("who", "who", NULL);
        printf("Error\n");
    }

    return 0;
}
