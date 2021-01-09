/**
 * Two children: 
 *      - One reads input and sends to the othre process
 *      - The other reads and prints
 * 
 * They communicate using shared memory.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define SHMLEN 2048

void check_err(int val, char* msg) {
    if(val == -1) {
        perror(msg);
        exit(1);
    }
}

void check_shm_err(char* val, char* msg) {
    if(val == (char*)-1) {
        perror(msg);
        exit(1);
    }
}

void producer(int shm, int sem) {
    struct sembuf SIGNAL[1] = { { 0, +1, 0 } };
    char* data_ptr;
    int len, retcode;

    // Attach process to shm
    data_ptr = (char*) shmat(shm, NULL, 0);
    check_shm_err(data_ptr, "shmat");

    // Write data onto shm
    while(strcmp(data_ptr, "quit") != 0) {
        printf("\033[36;1mInsert a string here: \033[0m");
        fgets(data_ptr, SHMLEN, stdin);

        // Remove \n
        len = strlen(data_ptr);
        if(data_ptr[len - 1] == '\n')
            data_ptr[--len] = '\0';

        // Send signal
        retcode = semop(sem, SIGNAL, 1);
        check_err(retcode, "semop");
    }
}

void consumer(int shm, int sem) {
    struct sembuf WAIT[1] = { { 0, -1, 0 } };
    char* data_ptr;
    int retcode;

    // Attach process to shm
    data_ptr = (char*) shmat(shm, NULL, SHM_RDONLY);
    check_shm_err(data_ptr, "shmat");

    while(strcmp(data_ptr, "quit") != 0) {
        // Wait to be able to read
        semop(sem, WAIT, 1);
        
        // Print data
        printf("\033[36;1m\t\t\tMessage received: %s\033[0m\n", data_ptr);
    }
}

int main(int argc, char** argv) {
    int retcode;
    int shm, sem;
    
    // Create shared memory area
    shm = shmget(IPC_PRIVATE, SHMLEN, IPC_CREAT | IPC_EXCL | 0660);
    check_err(shm, "shmget");

    // Create semaphore to sync 
    sem = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0660);
    check_err(sem, "semget");

    // Set starting semaphore value
    retcode = semctl(sem, 0, SETVAL, 0);
    check_err(retcode, "semctl");

    if(fork() != 0)  {
        if(fork() != 0) {
            wait(NULL);
            wait(NULL);
        }
        else
            producer(shm, sem);
    }
    else
        consumer(shm, sem);

}