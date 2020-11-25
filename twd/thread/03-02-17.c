/*
    Una variabile int n , inizializzata a 100, è condivisa tra 2 thread tI , tD .
    Il thread tI , ciclicamente:
        1. attende 100 ms (N.B.: la chiamata usleep(t) attende per t microsecondi )
        2. genera un int casuale tra 0 e 9 e lo somma alla variabile condivisa n
        3. se n è maggiore di 150 termina
        4. altrimenti ricomincia da (1), a meno che abbia già compiuto 1000 iterazioni, nel qual
        caso termina.
    Il thread tD , ciclicamente:
        1. attende 300 ms (N.B.: la chiamata usleep(n) attende per n microsecondi )
        2. genera un int casuale tra 0 e 9 e lo sottrae dalla variabile condivisa n
        3. se n è minore di 80 termina
        4. altrimenti ricomincia da (1), a meno che abbia già compiuto 1000 iterazioni, nel qual
        caso termina.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int n = 100;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* tI_fun(void* arg) {
    int i = 0;
    while(1) {
        i++;
        usleep(100);

        int x = rand() % 10;
        
        pthread_mutex_lock(&mutex);
        printf("\n%d + %d = %d", n, x, n + x);
        n = n + x;

        if(n > 150) {
            pthread_mutex_unlock(&mutex);
            printf("\nValore massimo n: %d", n);
            pthread_exit(NULL);
        }

        if(i >= 1000) {
            pthread_mutex_unlock(&mutex);
            printf("\nValore massimo ciclo per tI: %d", i);
            pthread_exit(NULL);
        }

        pthread_mutex_unlock(&mutex);
    }
}

void* tD_fun(void* arg) {
    int i = 0;

    while(1) {
        i++;
        usleep(300);

        int x = rand() % 10;

        pthread_mutex_lock(&mutex);
        printf("\n\t\t\t%d - %d = %d", n, x, n - x);
        n = n - x;

        if(n < 80) {
            pthread_mutex_unlock(&mutex);
            printf("\n\t\t\tValore minimo n: %d", n);
            pthread_exit(NULL);
        }

        if(i >= 1000) {
            pthread_mutex_lock(&mutex);
            printf("\n\t\t\tValore massimo ciclo per tD: %d", i);
            pthread_exit(NULL);
        }

        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char** argv) {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, tI_fun, NULL);
    pthread_create(&t2, NULL, tD_fun, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("\n ESECUZIONE TERMINATA");

}
