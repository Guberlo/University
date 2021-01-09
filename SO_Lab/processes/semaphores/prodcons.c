/**
 * Prod cons using semaphores and shm
 * 
 * We are going to use a FIFO queue to extract elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define MAXELEM 20
#define MEXNO 200

#define SEM_MUTEX 0
#define SEM_EMPTY 1
#define SEM_FULL 2


void check_err(int val, char* msg) {
    if(val == -1) {
        perror(msg);
        exit(1);
    }
}

void check_shm_err(int* val, char* msg) {
    if(*val == -1) {
        perror(msg);
        exit(1);
    }
}

int signalsem(int sem_id, int sem_num) {
    struct sembuf SIGNAL[1] = { { sem_num, +1, 0 } };
    return semop(sem_id, SIGNAL, 1);
}

int waitsem(int sem_id, int sem_num) {
    struct sembuf WAIT[1] = { { sem_num, -1 , 0 } };
    return semop(sem_id, WAIT, 1);
}

/**
 * Produce random number and insert on memory
 */
void producer(int shm, int sem) {
    int* data_ptr, *head, *tail;
    int number, len, sum;
    srand(time(NULL));

    // Attach shm
    data_ptr = shmat(shm, NULL, 0);
    check_shm_err(data_ptr, "shmat");

    // Head is saved on MAXELEM + 1
    head = data_ptr + MAXELEM;

    // Tail on MAXELEM + 2
    tail = data_ptr + MAXELEM + 1;

    // Init head and tail to 0
    *head = 0;
    *tail = 0;

    for(int i=0; i<MEXNO; i++) {
        // Get random number
        number = rand() % 1234;

        // Wait on EMPTY (free a slot)
        waitsem(sem, SEM_EMPTY);
        waitsem(sem, SEM_MUTEX);

        // Insert element
        data_ptr[*head] = number;
        *head = (*head + 1) % MAXELEM;

        printf("\033[36;1mProd: num=%d\t(head=%d tail=%d)\033[0m\n", number, *head, *tail);

        sum += number;

        signalsem(sem, SEM_MUTEX);
        signalsem(sem, SEM_FULL);

        usleep(rand() % 50000);
    }

    printf("\033[34;1mFINAL SUM: %d\033[0m\n", sum);
}

void consumer(int shm, int sem) {
    int* data_ptr, *head, *tail;
    int number, len, sum;

    // Attach shm
    data_ptr = shmat(shm, NULL, 0);
    check_shm_err(data_ptr, "shmat");

    head = data_ptr + MAXELEM;
    tail = data_ptr + MAXELEM + 1;

    for(int i=0; i<MEXNO; i++) {
        // Wait FULL (consume a slot)
        waitsem(sem, SEM_FULL);
        waitsem(sem, SEM_MUTEX);

        // Consume a number
        number = data_ptr[*tail];
        *tail = (*tail + 1) % MAXELEM;

        printf("\033[32;1m\t\t\t\t\t\t\t\tCons: num=%d\t(head=%d tail=%d)\033[0m\n", number, *head, *tail);

        sum += number;

        signalsem(sem, SEM_MUTEX);
        signalsem(sem, SEM_EMPTY);

        usleep(rand() % 50000);
    }
    printf("\033[36;1m\t\t\t\t\t\t\t\tFINAL SUM: %d\033[0m\n", sum);
}



int main(int argc, char** argv) {
    int shm, sem;
    int retcode;
    // Create shm
    shm = shmget(IPC_PRIVATE, sizeof(int) * MAXELEM + 2, IPC_CREAT | IPC_EXCL | 0660); // MAXELEM + 2 because we need to have a ref for head and tail
    check_err(shm, "shmget");

    // Create sem
    sem = semget(IPC_PRIVATE, 3, IPC_CREAT | IPC_EXCL | 0660);
    check_err(sem, "semget");

    // Initialize semaphores
    retcode = semctl(sem, SEM_MUTEX, SETVAL, 1);
    check_err(retcode, "semctl MUTEX");

    retcode = semctl(sem, SEM_EMPTY, SETVAL, MAXELEM);
    check_err(retcode, "semctl EMPTY");

    retcode = semctl(sem, SEM_FULL, SETVAL, 0);
    check_err(retcode, "semctl FULL");


    if(fork() != 0) {
        if(fork() != 0) {
            wait(NULL);
            wait(NULL);

            // Deallocate memory
            shmctl(shm, IPC_RMID, NULL);
            semctl(sem, 0, IPC_RMID);
        }
        else {
            producer(shm, sem);
        }
    }
    else {
        consumer(shm, sem);
    }
}