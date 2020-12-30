/*
    I thread hanno una variabile condivisa x inizializzata a 0.
    Il thread T1 esegue un ciclo infinito,
    comportandosi in ciascun ciclo come segue:   
        ● Controlla il valore di x
            ○ Se x >= 10 allora il thread si metterà in attesa.
        ● Incrementa il valore di x 
    Il Thread T2 invece:
        ● decrementa x
        ● Controlla il valore di x
            ○ Se x < 10 allora sveglierà il thread in attesa.-
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int x = 0;

void* t1_func(void* arg) {
    while(1) {

        pthread_mutex_lock(&mutex);
        printf("\nt1 x: %d", x);
        if(x >= 10) {
            printf("\nAspetto");
            pthread_cond_wait(&cond, &mutex);
        }
        x = x+1;
        printf("\nt1 add: %d", x);
        pthread_mutex_unlock(&mutex);

    }
}

void* t2_func(void* arg) {
    while(1) {

        pthread_mutex_lock(&mutex);
        printf("\n\t\t\tt2 x: %d", x);
        x = x-1;
        if(x < 10){
            printf("\n\t\t\tSveglio t1");
            pthread_cond_signal(&cond);
        }
        printf("\n\t\t\tt2 sub: %d", x);
        pthread_mutex_unlock(&mutex);
        
    }
}

int main(int argc, char** argv) {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, t1_func, NULL);
    pthread_create(&t2, NULL, t2_func, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}