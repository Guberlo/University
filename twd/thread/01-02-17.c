/*
    Scrivere un programma in C in cui tre thread aggiornano la stessa variabile globale condivisa sample, inizialmente posta a 50.

    Ogni thread ciclicamente genera un numero casuale compreso tra 10 e 90 e prova a sovrascrivere il valore corrente di sample. 
    Il thread mostra in output un messaggio che segue il modello “Sono il thread X: sample valeva Y, adesso vale Z”, con opportuni valori al posto di X, Y e Z.
    Se il valore casuale generato è uguale al valore attuale di sample il thread termina il suo ciclo, comunicando in output la propria terminazione.

    Quando tutti i thread sono terminati, il programma principale termina e mostra in output il valore finale di sample.

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int sample = 50;

void* t_func(void* arg) {
    int x = 0;
    int len = sizeof(arg);
    char t[len];
    sprintf(t, "%s", (char*) arg);

    while(1) {

        x = rand() % (91 - 10) + 10;

        pthread_mutex_lock(&mutex);
        printf("\nSono il thread %s: sample valeva %d, adesso vale %d", t, sample, x);

        if(sample == x) {
            sample = x;
            pthread_mutex_unlock(&mutex);
            printf("\n%s exit", t);
            pthread_exit(NULL);
        }

        sample = x;

        pthread_mutex_unlock(&mutex);
    }
}



int main(int argc, char** argv) {
    srand(time(NULL));

    pthread_t t1, t2, t3;

    pthread_create(&t1, NULL, t_func, (void*) "t1");
    pthread_create(&t2, NULL, t_func, (void*) "t2");
    pthread_create(&t3, NULL, t_func, (void*) "t3");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("\nESECUZIONE TERMINATA: %d\n", sample);
    pthread_mutex_destroy(&mutex);

    return 0;
}