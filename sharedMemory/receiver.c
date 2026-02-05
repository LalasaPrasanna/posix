#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#define SHM_NAME "/myshm"

int main() {
    int fd;
    char *ptr;
    fd = shm_open(SHM_NAME, O_RDONLY, 0666);
    ptr = mmap(NULL, 1024, PROT_READ, MAP_SHARED, fd, 0);
    printf(" %s\n", ptr);
    munmap(ptr, 1024);
    close(fd);
    shm_unlink(SHM_NAME);

    return 0;
}