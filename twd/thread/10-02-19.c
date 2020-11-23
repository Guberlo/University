
/**
    Scrivere in C/C++ o in Java un programma con due thread T1 e T2 .

I thread hanno una variabile condivisa x inizializzata con un intero compreso tra 0 e
10 (estremi inclusi).

Il thread T1 esegue un ciclo infinito, comportandosi in ciascun ciclo come segue:

    ● attende 100ms
    ● genera un valore casuale intero, sia Y , compreso tra 0 e 10 (estremi inclusi)
    ● confronta Y con la variabile condivisa x :
        ○ Se Y coincide con x scrive sulla standard output “RISPOSTA
          CORRETTA”, e termina l’esecuzione
        ○ Altrimenti, scrive “RISPOSTA SBAGLIATA”
    ● Se Y differisce da x in valore assoluto di 4 o più, T1 scrive “DORMO” e si
    mette in attesa e, quando viene svegliato, scrive: “SVEGLIATO”.

Il thread T2 invece, ciclicamente:

    ● attende 300 ms
    ● scrive sulla standard output: “SVEGLIATI T1!”
    ● sveglia T1

Il main si occupa di generare T1 e T2 , attende la terminazione di T1 e, se questa
avviene, scrive sulla standard output: “TUTTO FINITO” e termina.

In C, la chiamata usleep(ut) attende per ut microsecondi; in Java il metodo
sleep(mt) della classe Thread attende per mt millisecondi.

*/


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

int x;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* t1_fun() {
    while (1) {
        usleep(100);
        int y = rand() % 10 +1;

        pthread_mutex_lock(&mutex);

        if(y == x) {
            printf("\nRISPOSTA CORRETTA: %d == %d", x, y);
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
        else if(abs(y - x ) >= 4) {
            printf("\nDORMO: %d", abs(y - x ));
            pthread_cond_wait(&cond, &mutex);
            printf("\nSVEGLIATO");
        }
        else printf("\nRISPOSTA SBAGLIATA: %d == %d", x, y);

        pthread_mutex_unlock(&mutex);
    }
}

void* t2_fun() {
    while(1) {
        usleep(300);

        printf("\nSVEGLIATI T1!");
        pthread_cond_signal(&cond);

    }
}

int main(int argc, char** argv) {

    srand(time(NULL));

    x = rand() % 10;

    pthread_t t1, t2;

    pthread_create(&t1, NULL, t1_fun, NULL);
    pthread_create(&t2, NULL, t2_fun, NULL);

    pthread_join(t1, NULL);
    printf("\nTUTTO FINITO");

    return 0;
}