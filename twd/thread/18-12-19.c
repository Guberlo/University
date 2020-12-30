/*
    I thread hanno una variabile condivisa x inizializzata con un intero compreso
    tra 0 e 10 (estremi inclusi).
    Il thread T1 ha una variabile privata m ed esegue un ciclo infinito,
    comportandosi in ciascun ciclo come segue:
        ● Attende 100ms
        ● Genera un valore casuale intero compreso tra 0 e 10 (estremi inclusi) e
        lo memorizza in m
        ● Se x è uguale a -1 termina l’esecuzione
        ● Altrimenti, confronta m con la variabile condivisa x:
            ○ Se m e x coincidono stampa un messaggio “RISPOSTA CORRETTA”, setta x
        a -1 e termina l’esecuzione
            ○ Se la differenza in valore assoluto tra m ed x è maggiore di 5 stampa il
            messaggio “risposta MOLTO sbagliata” e si mette in attesa
            ○ Altrimenti, stampa il messaggio “risposta sbagliata”
    Il Thread T2 invece:
        ● Attende 300ms
        ● Sveglia T1
        ● Se x è uguale a -1 , termina l’esecuzione
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int x;

void* t1_fun(void* arg) {
    int m;

    while(1) {
        usleep(100);
        printf("\nT2");

        m = rand() % 11;

        pthread_mutex_lock(&mutex);
        if(x == -1) {
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
        
        if(x == m) {
            printf("\nRISPOSTA ESATTA: %d == %d", x, m);
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
        
        if(abs(m - x) > 5) {
            printf("\nRISPOSTA MOLTO SBAGLIATA: %d", abs(m - x));
            pthread_cond_wait(&cond, &mutex);
        }
        else 
            printf("\nRISPOSTA SBAGLIATA");
        pthread_mutex_unlock(&mutex);
    }
}

void* t2_fun(void* arg) {
    while(1) {
        usleep(300);
        printf("\nT2");
        pthread_cond_signal(&cond);

        pthread_mutex_lock(&mutex);
        if(x == -1) {
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char** argv) {
    srand(time(NULL));
    setbuf(stdout, NULL);
    
    x = rand() % 11;

    pthread_t t1, t2;

    pthread_create(&t1, NULL, t1_fun, NULL);
    pthread_create(&t2, NULL, t2_fun, NULL);

    pthread_join(t1, NULL);

    printf("\nENTRAMBI HANNO FINITO");
}