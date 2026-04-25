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
#include <sys/socket.h>

int prim(int);

int main(int argc, char** argv) {
    
    pid_t pid;
    int skt[2];


    socketpair(AF_UNIX, SOCK_STREAM, 0, skt);

    pid = fork();


    if (pid != 0) {
        close(skt[1]);
        
        int len = 8; // Ana are
        write(skt[0], &len, 4);
        write(skt[0], "Ana are", len);

        char msg[100];

        read(skt[0], &len, 4);
        read(skt[0], msg, len);

        printf("%s\n", msg);

        close(skt[0]);
    } else {
        close(skt[0]);
        
        char msg[100];
        int len;

        read(skt[1], &len, 4);
        read(skt[1], msg, len);

        strcat(msg, " mere");
        len = strlen(msg);

        write(skt[1], &len, 4);
        write(skt[1], msg, len);

        close(skt[1]);
    }


    return 0;
}