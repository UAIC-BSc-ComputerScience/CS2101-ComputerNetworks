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

    if ((pid = fork()) == -1) {
        printf("Eroare");
        exit(0);
    }

    if ((pid = fork()) == 0) {
        char cmd[4] = "ls";
        char *cmdp[5];
        cmdp[0] = "ls";
        cmdp[1] = "-a";
        cmdp[2] = "-l";
        cmdp[3] = NULL;

        execvp(cmd, cmdp);
    } else {
        wait(NULL);
        printf("DONE");
    }

}