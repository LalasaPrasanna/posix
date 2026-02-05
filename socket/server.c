#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#define PORT 8080
int server_fd;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void* client(void* arg) {
    char buffer[1024];
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int client_fd;
    while (1) {
        pthread_mutex_lock(&mutex);
        client_fd = accept(server_fd,
                           (struct sockaddr*)&client_addr,
                           &addr_len);
        pthread_mutex_unlock(&mutex);
        if (client_fd < 0)
            continue;
        printf("Client %d connected\n", client_fd);
        while (1) {
            int bytes = recv(client_fd, buffer, 5, 0);
            if (bytes <= 0) {
                printf("Client %d disconnected\n", client_fd);
                close(client_fd);
                break;
            }
            buffer[bytes] = '\0';
            printf("Client %d: %s", client_fd, buffer);
        }
    }
    return NULL;
}
int main() {
    struct sockaddr_in server_addr;
    pthread_t threads[5];
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_fd, 5);
    printf("Server listening on port %d...\n", PORT);
    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, client, NULL);
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }
    close(server_fd);
    return 0;
}
}