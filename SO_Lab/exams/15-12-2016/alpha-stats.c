/**
 * https://diraimondo.dmi.unict.it/wp-content/uploads/classes/so/lab-exams/?get=compito_2016-12-15.pdf
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

#define ALPHA_LEN 26
#define MUTEX 0

void check_err(int val, char* msg) {
    if(val == -1) {
        perror(msg);
        exit(1);
    }
}

void check_ptr_err(void* val, char* msg) {
    if(val == NULL) {
        perror(msg);
        exit(1);
    }
}

int WAIT(int sem, int sem_num) {
    struct sembuf WAIT[1] = {sem_num, -1, 0};
    return semop(sem, WAIT, 1);
}

int SIGNAL(int sem, int sem_num) {
    struct sembuf SIGNAL[1] = {sem_num, +1, 0};
    return semop(sem, SIGNAL, 1);
}

void count_letters(int shm, int sem, char* filename) {
    char* data_ptr;
    struct stat sb;
    int fd, index, retcode;
    int* counter;

    // Check if file is supported
    if(stat(filename, &sb) == -1 || !S_ISREG(sb.st_mode)) {
        printf("\033[31;1mERROR: file not supported\033[0m\n");
        exit(1);
    }

    // Open file
    fd = open(filename, O_RDONLY);
    check_err(fd, "open");

    // Map file
    data_ptr = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    check_ptr_err(data_ptr, "mmap");

    close(fd);

    // Attach to shm
    counter = shmat(shm, NULL, 0);
    check_ptr_err(counter, "shmat");

    for(int i=0; i<sb.st_size; i++) {
        if( (data_ptr[i] >= 'A' && data_ptr[i] <= 'Z') ) {
            index = data_ptr[i] - 65; // ASCII UPPER CHARACTERS => A: 65, B: 66..
            WAIT(sem, MUTEX);
            counter[index] = counter[index] + 1;
            SIGNAL(sem, MUTEX);

            
        }
        else if(( data_ptr[i] >= 'a' && data_ptr[i] <= 'z') ) {
            index = data_ptr[i] - 97; // ASCII LOWER CHARACTERS => a:97, b:98..
            WAIT(sem, MUTEX);
            counter[index] = counter[index] + 1;
            SIGNAL(sem, MUTEX);
        }
        usleep( (rand() % 1000) + 1); // wait from 1 micro second to 1 second
    }

    retcode = munmap(data_ptr, sb.st_size);
    check_err(retcode, "munmap");

    exit(0);
}

int main(int argc, char** argv) {
    int shm, sem;
    int retcode;
    int* counter;
    long int total = 0;
    float percentage;

    srand(time(NULL));

    if(argc < 2) {
        printf("\033[31;1mUSE: %s <file1> [file-2] [file-3]....\033[0m\n", argv[0]);
        exit(1);
    }

    // Create shm
    shm = shmget(IPC_PRIVATE, sizeof(int) * ALPHA_LEN, IPC_CREAT | IPC_EXCL | 0660);
    check_err(shm, "shmget");

    // Create sem
    sem = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0660);
    check_err(sem, "semget");

    retcode = semctl(sem, MUTEX, SETVAL, 1);
    check_err(retcode, "semctl");

    // Init shm to 0
    counter = shmat(shm, NULL, 0);
    check_ptr_err(counter, "shmat");

    for(int i=0; i<ALPHA_LEN; i++)
        counter[i] = 0;

    for(int i=1; i<argc; i++) {
        if(fork() == 0)
            count_letters(shm, sem, argv[i]);
    }

    for(int i=1; i<argc; i++)
        wait(NULL);

    for(int i=0; i<ALPHA_LEN; i++)
        total += counter[i];

    for(int i=0; i<ALPHA_LEN; i++) {
        percentage = ((float) counter[i] / (float) total) * 100;

        printf("\033[33;1m%c: %5.2f%%\033[0m\n", i+97, percentage);
    }
    shmctl(shm, IPC_RMID, NULL);
    semctl(sem, MUTEX, IPC_RMID);

}