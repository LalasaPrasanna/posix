
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SHM_NAME "/myshm"

int main() {
    int fd;
    char *ptr;
    fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, 1024);
    ptr = mmap(NULL, 1024, PROT_WRITE, MAP_SHARED, fd, 0);
    strcpy(ptr, "Hello!");

    return 0;
}
