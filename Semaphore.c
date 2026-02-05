#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
 
pthread_t t1, t2;
sem_t s1,s2;

int counter = 0;
void* thread1(void* arg)
{
    while (1) {
        sem_wait(&s1);
        if (counter >= 100) {
            sem_post(&s2);
            break;
        }
            counter++;
            printf("t1 count: %d\n", counter);
            sem_post(&s2);
    }
    pthread_exit(NULL);
}
 
void* thread2(void* arg)
{
    while (1) {
        sem_wait(&s2);
        if (counter >= 100) {
            sem_post(&s1);
            break;
        }
            counter++;
            printf("t2 count: %d\n", counter);
            sem_post(&s1);
    }
    pthread_exit(NULL);
}
 
int main()
{
    sem_init(&s1,0,1);
    sem_init(&s2,0,0);
 
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
 
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&s1);
    sem_destroy(&s2);
 
    printf("all threads terminated\n");
    return 0;
}
 