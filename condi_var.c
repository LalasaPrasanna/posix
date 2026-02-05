#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int counter = 0;
int turn = 0;
int exit_flag = 0;
void *thread1(void *arg)
{
    while (1) {
        pthread_mutex_lock(&mutex);
        while(turn != 0 && !exit_flag)
            pthread_cond_wait(&cond, &mutex);
        if (exit_flag){
            pthread_mutex_unlock(&mutex);
            break;
        }
        counter++;
        printf("t1 count: %d\n", counter);
        if (counter >= 100) {
            exit_flag =  1;
        }
        turn = 1;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex); 
    }
    pthread_exit(NULL);
}
void* thread2(void* arg)
{
        while (1) {
        pthread_mutex_lock(&mutex);
        while(turn != 1 && !exit_flag)
            pthread_cond_wait(&cond, &mutex);
        if (exit_flag){
            pthread_mutex_unlock(&mutex);
            break;
        }
        counter++;
        printf("t2 count: %d\n", counter);
        if (counter >= 100) {
            exit_flag =  1;
        }
        turn = 0;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex); 
    }
    pthread_exit(NULL);
}
int main()
{
    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
 
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("all threads terminated\n");
    return 0;
}