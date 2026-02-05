#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    char buffer[100];

    pipe(fd);           

    if (fork() == 0) {  
        close(fd[1]);
        read(fd[0], buffer, sizeof(buffer));
        printf(" %s\n", buffer);
        close(fd[0]);
    } else {            
        close(fd[0]);
        write(fd[1], "Hello", 6);
        close(fd[1]);
    }
    return 0;
}
