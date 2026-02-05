#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
 
pthread_t t1, t2;
 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barrier;
 
int counter = 0;
 
void* thread1(void* arg)
{
    while (1) {
        pthread_barrier_wait(&barrier);   
        pthread_mutex_lock(&mutex);
        if (counter >= 100) {
            pthread_mutex_unlock(&mutex);
            pthread_barrier_wait(&barrier);  
            break;
        } 
        if (counter % 2 == 0 ) {
            counter++;
            printf("t1 count: %d\n", counter);
        } 
        pthread_mutex_unlock(&mutex); 
    }
    pthread_exit(NULL);
} 
void* thread2(void* arg)
{
    while (1) {
        pthread_barrier_wait(&barrier); 
        pthread_mutex_lock(&mutex); 
        if (counter >= 100) {
            pthread_mutex_unlock(&mutex);
            pthread_barrier_wait(&barrier); 
            break;
        }
        if (counter % 2 == 1) {
            counter++;
            printf("t2 count: %d\n", counter);
        }
        pthread_mutex_unlock(&mutex);   
    }
    
    pthread_exit(NULL);
}
 
int main()
{
    pthread_barrier_init(&barrier, NULL, 2);
 
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
 
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
 
    pthread_barrier_destroy(&barrier);
 
    printf("all threads terminated\n");
    return 0;
}
 