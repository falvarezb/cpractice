#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

// cat /proc/pid/maps -> Linux
// sudo pmap -x pid -> Linux
// vmmap --wide pid -> Apple

void* thread_body(void* arg) {
    pid_t pid = getpid();
    printf("pid=%d\n", pid);
    printf("pid addr=%p\n", &pid); //must be an address in this thread's stack
    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t thread1;
    pthread_t thread2;

    pthread_create(&thread1, NULL, thread_body, NULL);
    pthread_create(&thread2, NULL, thread_body, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}