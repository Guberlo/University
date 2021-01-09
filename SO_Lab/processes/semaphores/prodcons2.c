/**
 * One producer and two consumers using semaphores and shm
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

int SIGNAL(int sem_id, int sem_num) {
    struct sembuf SIGNAL[1] = { { sem_num, +1, 0 } };
    return semop(sem_id, SIGNAL, 1);
}

int WAIT(int sem_id, int sem_num) {
    struct sembuf WAIT[1] = { { sem_num, -1, 0 } };
    return semop(sem_id, WAIT, 1);
}

void producer(int shm, int sem) {
    int* data_ptr, *head, *tail;
    int number, sum, len;
    srand(time(NULL));

    // Attach shm
    data_ptr = shmat(shm, NULL, 0);
    check_shm_err(data_ptr, "shmat");

    // Init head and tail
    head = data_ptr + MAXELEM;
    tail = data_ptr + MAXELEM + 1;

    *head = 0;
    *tail = 0;

    for(int i=0; i<MEXNO; i++) {
        number = rand() % 132;

        WAIT(sem, SEM_EMPTY);
        WAIT(sem, SEM_MUTEX);
        // Insert element
        data_ptr[*head] = number;
        // Increment head
        *head = (*head + 1) % MAXELEM;

        printf("\033[35;1mProd: num=%d\t(head=%d tail=%d)\033[0m\n", number, *head, *tail);
        sum += number;

        SIGNAL(sem, SEM_MUTEX);
        SIGNAL(sem, SEM_FULL);

        usleep(rand() % 50000);
    }
    printf("\033[36;1mPROD: sum=%d\033[0m\n", sum);
}

void consumer(int shm, int sem, int index) {
    int* data_ptr, *head, *tail;
    int sum;

    // Attach shm
    data_ptr = shmat(shm, NULL, 0);
    check_shm_err(data_ptr, "shmat");

    head = data_ptr + MAXELEM;
    tail = data_ptr + MAXELEM + 1;

    for(int i=0; i<MEXNO / 2; i++) {
        WAIT(sem, SEM_FULL);
        WAIT(sem, SEM_MUTEX);

        printf("\033[32;1m\t\t\t\t\t\t\t\tCons %d: num=%d\t(head=%d tail=%d)\033[0m\n", index, data_ptr[*tail], *head, *tail);

        sum += data_ptr[*tail];
        *tail = (*tail + 1) % MAXELEM;

        SIGNAL(sem, SEM_MUTEX);
        SIGNAL(sem, SEM_EMPTY);

        usleep(rand() % 50000);
    }
    printf("\033[34;1m\t\t\t\t\t\t\t\tCONS %d: sum=%d\033[0m\n", index, sum);
}

int main(int argc, char** argv) {
    int shm, sem;
    int retcode;

    // Create shm
    shm = shmget(IPC_PRIVATE, sizeof(int) * MAXELEM + 2, IPC_CREAT | IPC_EXCL | 0660);
    check_err(shm, "shmget");

    // Create sem
    sem = semget(IPC_PRIVATE, 3, IPC_CREAT | IPC_EXCL | 0660);
    check_err(sem, "semget");

    // Init sems
    retcode = semctl(sem, SEM_MUTEX, SETVAL, 1);
    check_err(retcode, "semctl");

    retcode = semctl(sem, SEM_EMPTY, SETVAL, MAXELEM);
    check_err(retcode, "semctl");

    retcode = semctl(sem, SEM_FULL, SETVAL, 0);
    check_err(retcode, "semctl");

    if(fork() != 0) {
        if(fork() != 0) {
            if(fork() != 0) {
                wait(NULL);
                wait(NULL);
                wait(NULL);

                shmctl(shm, IPC_RMID, NULL);
                semctl(sem, 0, IPC_RMID);
            }
            else 
                consumer(shm, sem, 1);
        }
        else
            consumer(shm, sem, 2);
    }
    else
        producer(shm, sem); 
}