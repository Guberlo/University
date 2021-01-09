/**
 * Bank transactions using semaphores
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h> 

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

int main(int argc, char** argv) {
    int shm, sem;
    int* bank_account;
    int retcode;
    int transf = 2000;

    struct sembuf SIGNAL[1] = { { 0, +1 ,0 } };
    struct sembuf WAIT[1] = { { 0, -1, 0 } };

    // Create shm
    shm = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | IPC_EXCL | 0660);
    check_err(shm, "shmget");

    // Create sem
    sem = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0660);
    check_err(sem, "semget");

    // Init semaphore
    retcode = semctl(sem, 0, SETVAL, 1);
    check_err(retcode, "semctl");

    // Attach to shm
    bank_account = (int*) shmat(shm, NULL, 0);
    check_shm_err(bank_account, "shmat");

    // Initialize bank account to 0
    *bank_account = 0;

    if(fork() == 0) {
        for(; transf > 0; transf--) {
            // We need to protect the critical region: WAIT
            printf("\033[31;1mWAITING\033[0m\n");
            retcode = semop(sem, WAIT, 1);
            check_err(retcode, "semop");

            // Increment
            printf("\033[36;1mP1: read=%d\twrote=%d\033[0m\n", *bank_account, *bank_account+1);
            *bank_account = *bank_account + 1;

            // SIGNAL
            printf("\033[31;1mSIGNALING\033[0m\n");
            retcode = semop(sem, SIGNAL, 1);
            check_err(retcode, "semop");
            usleep(rand() % 500);
        }
        exit(0);
    }
    else if(fork() == 0) {
        for(; transf > 0; transf--) {
            // WAIT
            printf("\033[31;1m\t\t\tWAITING\033[0m\n");
            retcode = semop(sem, WAIT, 1);
            check_err(retcode, "semop");

            // Decrement
            printf("\033[36;1mP2: read=%d\twrote=%d\033[0m\n", *bank_account, *bank_account - 1);
            *bank_account = *bank_account - 1;

            // SIGNAL
            printf("\033[31;1m\t\t\tSIGNALING\033[0m\n");
            retcode = semop(sem, SIGNAL, 1);
            check_err(retcode, "semop");
            usleep(rand() % 500);
        }
        exit(0);
    }

    wait(NULL);
    wait(NULL);

    printf("\033[35;1mFINAL VALUE: %d\033[0m\n", *bank_account);

}