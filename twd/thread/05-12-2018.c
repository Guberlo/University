#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int m = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* t1_func() {
    while(1) {
        pthread_mutex_lock(&mutex);
        int m0 = m;
        printf("\nT1->m0 = %d", m0);
        m = rand();
        usleep(300);
        if(m0 %2 != 0) {
            printf("\nm0 dispari: %d!", m0);
            pthread_cond_wait(&cond, &mutex);
        }
        pthread_mutex_unlock(&mutex);
    }
}

void* t2_func() {
    while(1) {
        pthread_mutex_lock(&mutex);
        int m0 = m;
        printf("\n\t\t\tT2->m0 = %d", m0);
        m = rand();
        usleep(300);
        if(m0 %2 == 0) {
            printf("\n\t\t\tm0 pari: %d!", m0);
            pthread_cond_wait(&cond, &mutex);
        }
        pthread_mutex_unlock(&mutex);
    }
}

void* t3_func(void* arg) {
    while(1) {
        printf("\n\t\t\t\t\t\t T3->broadcast");
        pthread_cond_broadcast(&cond);
        sleep(2);
    }
}

int main(int argc, char** argv) {
    pthread_t t1, t2, t3;

    pthread_create(&t1, NULL, t1_func, NULL);
    pthread_create(&t2, NULL, t2_func, NULL);
    pthread_create(&t3, NULL, t3_func, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("\n ESECUZIONE TERMINATA");



}