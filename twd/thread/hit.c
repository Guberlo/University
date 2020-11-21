/*
    You can find more information about the exercise here
    https://docs.google.com/document/d/1vKfI6kAV5YDa3vqCGF5KMyY_MJ8EF-XOlQaO1cZyNVw/edit
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

int x = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* increment_and_check(void* arg) {
    int hit;

    while(1) {
        usleep(rand() % 100000 + 1);

        pthread_mutex_lock(&mutex);
        if(x > 500) {
            printf("Thread %s -> x: %d\n", (char*) arg, x);
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
        else {
            x++;
            hit = x;
            printf("Thread %s -> x: %d\n", (char*) arg, x);
        }
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main(int argc, char** argv) {
    pthread_t tA, tB;

    pthread_create(&tA, NULL, increment_and_check, (void*) "A");
    pthread_create(&tB, NULL, increment_and_check, (void*) "B");

    pthread_join(tA, NULL);
    pthread_join(tB, NULL);

    printf("\nBoth thread terminated, x = %d\n", x);
}