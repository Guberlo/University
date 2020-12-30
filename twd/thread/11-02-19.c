#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* t1_fun(void* arg) {
    int m;

    while(1) {
        m = rand();

        if(m % 2 == 0) {
            usleep(300);
            printf("\n%d", m);
        }
        else {
            printf("\nDORMO");
            pthread_cond_wait(&cond, &mutex);
        }
    }
}

void* t2_fun(void* arg) {
    while(1) {
        pthread_cond_signal(&cond);

        sleep(8);
    }
}

int main(int argc, char** argv) {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, t1_fun, NULL);
    pthread_create(&t2, NULL, t2_fun, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}



