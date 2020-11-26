/*
    Una variabile intera n, inizializzata a 0, è condivisa tra 2 thread tO, tE.
    Il thread tE, ciclicamente:
        attende 200 ms (N.B.: la chiamata usleep(t) attende per t microsecondi)
        genera un int casuale pari e lo somma alla variabile condivisa n
        se ha eseguito almeno 10 cicli e n è pari termina
        altrimenti ricomincia dal passo (1), a meno che abbia già compiuto 1000 iterazioni, nel qual caso termina.
    Il thread tO, ciclicamente:
        attende 200 ms (N.B.: la chiamata usleep(n) attende per n microsecondi)
        genera un int casuale dispari e lo somma alla variabile condivisa n
        se ha eseguito almeno 10 cicli e n è dispari termina
        altrimenti ricomincia dal passo (1), a meno che abbia già compiuto 1000 iterazioni, nel qual caso termina.

    (Non ricorrere a un array di 2 thread per l’implementazione!)

    Il programma termina quando tutti i thread hanno terminato la propria esecuzione. I thread scriveranno di essere terminati. Possono anche visualizzare, a ogni ciclo, il valore trovato in n.
    Nel codice, proteggere opportunamente la variabile n dagli accessi concorrenti.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int n = 0;

void* tO_func(void* arg) {
    int x, i = 0;
    while(1) {
        i++;
        usleep(200000);
        x = rand() % 10;

        if(x % 2 == 0)
            x++;
        
        pthread_mutex_lock(&mutex);
        printf("\ntO sum: %d + %d = %d", n, x, n+x);
        n = n + x;

        if(i >= 10 && n % 2 != 0) {
            printf("\nt0 exit: %d, %d", i, n);
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }

        if(i >= 1000) {
            printf("\nt0 exit: %d", i);
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
        pthread_mutex_unlock(&mutex);
    }
}

void* tE_func(void* arg) {
    int x, i = 0;
    while(1) {
        i++;
        usleep(200000);
        x = rand() % 10;

        if(x % 2 != 0)
            x++;
        
        pthread_mutex_lock(&mutex);
        printf("\n\t\t\ttE sum: %d + %d = %d", n, x, n+x);
        n = n + x;

        if(i >= 10 && n % 2 == 0) {
            printf("\n\t\t\ttE exit: %d, %d", i, n);
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }

        if(i >= 1000) {
            printf("\n\t\t\ttE exit: %d", i);
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char** argv) {
    srand(time(NULL));

    pthread_t tO, tE;

    pthread_create(&tO, NULL, tO_func, NULL);
    pthread_create(&tE, NULL, tE_func, NULL);

    pthread_join(tO, NULL);
    pthread_join(tE, NULL);

    printf("\nESECUZIONE TERMINATA\n");

}