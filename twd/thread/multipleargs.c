/*
    Shows how to pass multiple arguments to a thread
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

struct thrd_arg {
    char* name;
    int value;
};

void* printargs(void* arg) {
    struct thrd_arg obj = *(struct thrd_arg*) arg;
    char* name = obj.name;
    int value = obj.value;

    for(int i=0; i<9; i++) {
        printf("Name: %s\t\tValue:%d\n", name, value);
        usleep(1+value%2);
    }
    return NULL;
}

int main(int argc, char** argv) {
    pthread_t t1, t2;
    struct thrd_arg arg1, arg2;

    arg1.name = "Thread 1"; arg1.value = 55;
    arg2.name = "Thread 2"; arg2.value = 241;

    pthread_create(&t1, NULL, printargs, &arg1);
    pthread_create(&t2, NULL, printargs, &arg2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

}