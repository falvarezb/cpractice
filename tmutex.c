#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mtx;
pthread_spin_t spin;

void* thread_body1(void* arg) {
    int* x = (int *) arg;
    for (size_t i = 0; i < 1000; i++)
    {
        pthread_mutex_lock(&mtx);
        *x += 1; 
        pthread_mutex_unlock(&mtx);
    }
    
    
    return NULL;
}

void* thread_body2(void* arg) {
    int* x = (int *) arg;
    for (size_t i = 0; i < 1000; i++)
    {
        pthread_mutex_lock(&mtx);
        *x += 2; 
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}



int main(int argc, char const *argv[])
{
    int shared_x = 0;
    pthread_t thread1, thread2;

    pthread_mutex_init(&mtx, NULL);

    int result1 = pthread_create(&thread1, NULL, thread_body1, &shared_x);
    int result2 = pthread_create(&thread2, NULL, thread_body2, &shared_x);
    if (result1 | result2)
    {
        printf("threads failed to be created\n");
        return 1;
    }

    result1 = pthread_join(thread1, NULL);
    result2 = pthread_join(thread2, NULL);

    if (result1 | result2)
    {
        printf("threads failed to be joined\n");
        return 2;
    }

    printf("thread1: %d\n", shared_x);
    

    return 0;
}
