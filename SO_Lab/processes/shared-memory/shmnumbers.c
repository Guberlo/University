/**
 * Shared memory: child 1 gets input and saves them on shared memory
 *                child 2 reads from shared memory
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define MAXMSG 40

void check_err(int val, char* msg) {
    if(val == -1) {
        perror(msg);
        exit(1);
    }
}

void check_ptr_err(int* ptr, char* msg) {
    if( *ptr == -1) {
        perror(msg);
        exit(1);
    }
}

void producer(int shm) {
    int* retptr;
    int number, i;

    printf("\033[32;1mPRODUCER STARTED\033[0m\n");

    // Attach process to shared memory area
    retptr = (int*) shmat(shm, NULL, 0);
    check_ptr_err(retptr, "shmat");

    for(i=1; i<MAXMSG; i++) {
        printf("\033[34;1mInsert a number(0 to exit): \033[0m");
        scanf("%d", &number);

        if(number == 0)
            break;
        
        retptr[i] = number;
    }

    // Write how many numbers have been written
    retptr[0] = i;
}

void consumer(int shm) {
    int* retptr;
    int len;

    printf("\033[34;1m\t\t\tCONSUMER STARTED\033[0m\n");

    retptr = (int*) shmat(shm, NULL, SHM_RDONLY);
    check_ptr_err(retptr, "shmat consumer");

    len = retptr[0];

    printf("\033[34;1mNumbers read: ");
    for(int i=1; i<len; i++) {
        printf("%d ", retptr[i]);
    }
    printf("\033[0m\n");

}

int main(int argc, char** argv) {
    int shm_fd, pid;

    // Create shm area
    shm_fd = shmget(IPC_PRIVATE, sizeof(int) * MAXMSG + 1, IPC_CREAT | IPC_EXCL | 0660);
    check_err(shm_fd, "shmget");

    // First write data, then consume
    pid = fork();

    if(pid == 0)
        producer(shm_fd);
    else
        wait(NULL);

    // Consume data
    pid = fork();

    if(pid == 0)
        consumer(shm_fd);
    else
        wait(NULL);
    
    shmctl(shm_fd, IPC_RMID, NULL);
}