#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* task(void* arg) {
    sleep(1);
    printf("Task executed in pthread.\n");
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, task, NULL);
    //pthread_join(thread, NULL); //resourcces leak without this, silently
    printf("Exiting main without joining pthread.\n");
    return 0;
}