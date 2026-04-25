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

int prim(int);

int main(int argc, char** argv) {
    
    pid_t pid;
    int fd[2];

    if ( pipe(fd) == -1 ) {
        exit(1);
    }

    if ( (pid = fork()) == -1 ) {
        exit(1);
    }

    int n = 131;

    if (pid != 0) {
        
        write(fd[1], &n, 4); // -1

        wait(NULL);

        int res;
        read(fd[0], &res, 4);

        if (res == 0) {
            printf("Nope\n");
        } else if (res == 1) {
            printf("Yes\n");
        }

    } else {

        int nr;

        read(fd[0], &nr, 4); // -1
        
        int result = prim(nr);
        write(fd[1], &result, 4);

    }
    
    return 0;
}

int prim(int n) {

    if (n <= 1) {
        return 0;
    }

    for (int i = 2; i < n; i++) 
        if (n % i == 0) 
            return 0; 

    return 1;
} 

