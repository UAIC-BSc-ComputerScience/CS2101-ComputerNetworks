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

int main() {
    pid_t pid;

    mkfifo("./fifo", 0600);

    char message[100] = "fortune";

    int fdR = open("./fifo", O_RDONLY | O_NONBLOCK);

    int fdW = open("./fifo", O_WRONLY);


    if ((pid = fork()) == -1) {
        printf("Eroare");
    }

    if (pid == 0) {

        int n = getpid();

        write(fdW, &n, 4);

        if (n % 2 == 0) {
            char message[10];

            read(fdR, message, 8);

            printf("%s\n", message);
        }

    } else {
        int child;

        read(fdR, &child, 4);

        if (child % 2 == 0) {
            write(fdW, message, 8);
        } else {
            printf("Lost\n");
            exit(0);
        }

    }


}