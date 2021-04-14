#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#define SIZE 1000

sem_t *semaphore;

void* thread_body1(void* arg) {
    int* x = (int *) arg;
    for (size_t i = 0; i < SIZE; i++)
    {
        sem_wait(semaphore);
        *x += 1; 
        sem_post(semaphore);
    }
    return NULL;
}

void* thread_body2(void* arg) {
    int* x = (int *) arg;
    for (size_t i = 0; i < SIZE; i++)
    {
        sem_wait(semaphore);
        *x += 2; 
        sem_post(semaphore);        
    }
    return NULL;
}



int main(int argc, char const *argv[])
{
    int shared_x = 0;
    pthread_t thread1, thread2;

#ifdef __APPLE__
    semaphore = sem_open("sem0", O_CREAT, 0644, 1);
    if (semaphore == SEM_FAILED)
    {
        perror("error creating semaphore\n");
        return 1;
    }
    
#else
    sem_t local_semaphore;
    semaphore = &local_semaphore;
    sem_init(semaphore, 0, 1);
#endif

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
        return 1;
    }

    printf("result: %d\n", shared_x);

#ifdef __APPLE__
    sem_close(semaphore);
    sem_unlink("sem0");
#else
    sem_destroy(semaphore);
#endif
    

    return 0;
}
