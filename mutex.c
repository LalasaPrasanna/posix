#include <stdio.h>
#include <pthread.h>

int counter = 0;
pthread_mutex_t mutex;

void* thread(void* arg) {
    for (int i = 0; i < 100; i++) {
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&t1, NULL, thread, NULL);
    pthread_join(t1, NULL);

    pthread_mutex_destroy(&mutex);

    printf("Counter value: %d\n", counter);
    return 0;
}
