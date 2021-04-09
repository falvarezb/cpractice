// gcc -DCOND_VAR tcv.c -o tcv -lpthread

#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mtx;
int done = 0;
pthread_cond_t cv; //conditional variable

void f1() {
    printf("thread1\n");
    done = 1;
}

void f2() {
    printf("thread2\n");
}

void* thread_body1() {
#ifdef COND_VAR
    pthread_mutex_lock(&mtx);
    f1();
    pthread_cond_signal(&cv);
    pthread_mutex_unlock(&mtx);

#else 
    f1();
#endif

    return NULL;
}

void* thread_body2() {
#ifdef COND_VAR
    pthread_mutex_lock(&mtx);
    while (!done)
    {
        pthread_cond_wait(&cv, &mtx); //sleep/notify
    }
    f2();
    pthread_mutex_unlock(&mtx);

#else
    while (!done)
    {
        //busy wait        
    }
    f2();
#endif

    return NULL;
}


int main(int argc, char const *argv[])
{
    pthread_t thread1, thread2;    

#ifdef COND_VAR
    pthread_mutex_init(&mtx, NULL);
    pthread_cond_init(&cv, NULL);
#endif

    clock_t t = clock();

    int result1 = pthread_create(&thread1, NULL, thread_body1, NULL);
    int result2 = pthread_create(&thread2, NULL, thread_body2, NULL);
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

    t = clock() - t;
    printf ("It took me %lu clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    
#ifdef COND_VAR
    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cv);
#endif

    return 0;
}
