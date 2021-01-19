/**
 * SHM = 10:
 * P: INSERT. SEM_EMPTY = 10 --> foreach insert WAIT(SEM_EMPTY) SIGNAL(SEM_FULL) # così si bloccherà se il buffer è pieno e sveglierà il consumer
 * M: CONSUME, INSERT. SEM_EMPTY = 10, SEM_FULL = 0 --> foreach consume WAIT(SEM_FULL) modify  SIGNAL(SEM_FULLMOD)
 * O: CONSUME --> WAIT(SEM_FULLMOD) .... SIGNAL(EMPTY)
 * struct with: number, mod (?), eof
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MUTEX 0
#define EMPTY 1
#define FULL 2
#define FULL_MOD 3

#define DIM_ELE 10
#define STRLEN 1024

typedef enum {
    TYPE_NUMBER,
    TYPE_MODULE,
    TYPE_FREE,
    TYPE_EOF
} mtype;

typedef struct {
    long number;
    mtype type;
} shmsg;

int WAIT(int sem, int sem_num) {
    struct sembuf WAIT[1] = {sem_num, -1, 0};
    return semop(sem, WAIT, 1);
}

int SIGNAL(int sem, int sem_num) {
    struct sembuf SIGNAL[1] = {sem_num, +1, 0};
    return semop(sem, SIGNAL, 1);
}

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

char* get_type(mtype type) {
    switch (type) {
        case TYPE_EOF:
            return "TYPE_EOF";
        case TYPE_FREE:
            return "TYPE_FREE";
        case TYPE_MODULE:
            return "TYPE_MODULE";
        case TYPE_NUMBER:
            return "TYPE_NUMBER";
        default:
            return "BOH";
    }
}

void read_file(int shm, int sem, char* filename) {
    int retcode, i;
    long number;
    char* line;
    struct stat sb;
    FILE* file;
    shmsg* data_ptr;

    printf("\033[33;1mREAD START\033[0m\n");

    // Check if file is supported
    if(lstat(filename, &sb) == -1 || !S_ISREG(sb.st_mode) || (file = fopen(filename, "r")) == NULL) {
        printf("\033[31;1mERROR: file not supported\033[0m\n");

        retcode = shmctl(shm, IPC_RMID, NULL);
        check_err(retcode, "shmctl rm");

        retcode = semctl(sem, 0, IPC_RMID);
        check_err(retcode, "semctl rm");
        exit(1);
    }

    // Attach to shm
    data_ptr = shmat(shm, NULL, 0);
    check_ptr_err(data_ptr, "shmat read file");

    // Init shm to free
    for(int i=0; i<DIM_ELE; i++) {
        data_ptr[i].type = TYPE_FREE;
    }

    // Read from file
    line = malloc(STRLEN);
    while((line = fgets(line, STRLEN, file)) != NULL) {
        number = atol(line);
        // printf("atoi %s: %ld\n", line, number);

        // Insert number in shm
        WAIT(sem, EMPTY);
        WAIT(sem, MUTEX);

        // Check for a free slot
        for(i=0; i<DIM_ELE; i++) {
            if(data_ptr[i].type == TYPE_FREE) {
                data_ptr[i].type = TYPE_NUMBER;
                data_ptr[i].number = number;
                printf("\033[33;1m%d: insert: %ld\033[0m\n", i, number);
                break;
            }
        }

        SIGNAL(sem, MUTEX);
        SIGNAL(sem, FULL);
    }

    printf("\033[33;1mSENDING EOF\033[0m\n");

    // Send EOF
    WAIT(sem, EMPTY);
    WAIT(sem, MUTEX);

    for(i=0; i<DIM_ELE; i++) {
        if(data_ptr[i].type == TYPE_FREE) {
            data_ptr[i].type = TYPE_EOF;
            break;
        }
    }    

    SIGNAL(sem, MUTEX);
    SIGNAL(sem, FULL);

    fclose(file);
    free(line);
}

void calculate_mod(int shm, int sem, char* module) {
    int i, eof=0;
    long mod = atol(module);
    shmsg* data_ptr;

    printf("\033[35;1m\t\t\tCALC MOD STARTED\033[0m\n");

    // Attach to shm
    data_ptr = shmat(shm, NULL, 0);
    check_ptr_err(data_ptr, "shmat calc mod");

    while(1) {
        WAIT(sem, FULL);
        WAIT(sem, MUTEX);

        for(i=0; i<DIM_ELE; i++) {
            if(data_ptr[i].type == TYPE_NUMBER) {
                data_ptr[i].type = TYPE_MODULE;
                printf("\033[35;1m\t\t\t%d mod: %d\033[0m\n", data_ptr[i].number, data_ptr[i].number % mod);
                data_ptr[i].number = data_ptr[i].number % mod;
                break;
            }
            else if(data_ptr[i].type == TYPE_EOF) {
                eof = 1;
            }
        }

        SIGNAL(sem, MUTEX);
        SIGNAL(sem, FULL_MOD);

        if(eof && i==DIM_ELE)
            break;
    }

    printf("\033[35;1m\t\t\tCALC MOD FINISHED\033[0m\n");
    exit(0);
}

void mod_print(int shm, int sem) {
    int i, eof = 0;
    shmsg* data_ptr;

    printf("\033[36;1m\t\t\t\t\t\t\tMOD PRINT STARTED\033[0m\n");

    // Attach to shm
    data_ptr = shmat(shm, NULL, 0);
    check_ptr_err(data_ptr, "shmat mod print");

    while(1) {
        WAIT(sem, FULL_MOD);
        WAIT(sem, MUTEX);

        for(i=0; i<DIM_ELE; i++) {
            if(data_ptr[i].type == TYPE_MODULE) {
                printf("\033[36;1m\t\t\t\t\t\t\tmodule: %ld\033[0m\n", data_ptr[i].number);
                data_ptr[i].type = TYPE_FREE;
                break;
            }
            else if(data_ptr[i].type == TYPE_EOF) {
                eof = 1;
            }
        }

        SIGNAL(sem, MUTEX);
        SIGNAL(sem, EMPTY);

        if(eof && i==DIM_ELE)
            break;
    }

    printf("\033[36;1m\t\t\t\t\t\t\tMOD PRINT FINISHED\033[0m\n");
    exit(0);
}

int main(int argc, char** argv) {
    int shm, sem;
    int retcode;

    if(argc != 3) {
        printf("\033[31;1mUSE: %s <input-file> <mod number>\033[0m\n", argv[0]);
        exit(1);
    }

    // Create shm
    shm = shmget(IPC_PRIVATE, sizeof(shmsg) * DIM_ELE, IPC_CREAT | IPC_EXCL | 0660);
    check_err(shm, "shmget");

    // Create sem
    sem = semget(IPC_PRIVATE, 4, IPC_CREAT | IPC_EXCL | 0660);
    check_err(sem, "semget");

    // Init sem
    retcode = semctl(sem, MUTEX, SETVAL, 1);
    check_err(retcode, "semctl MUTEX");

    retcode = semctl(sem, EMPTY, SETVAL, DIM_ELE);
    check_err(retcode, "semctl EMPTY");

    retcode = semctl(sem, FULL, SETVAL, 0);
    check_err(retcode, "semctl FULL");

    retcode = semctl(sem, FULL_MOD, SETVAL, 0);
    check_err(retcode, "semctl FULLMOD");

    // Fork
    if(fork() != 0) {
        if(fork() != 0) {
            read_file(shm, sem, argv[1]);
            wait(NULL);
            wait(NULL);

            retcode = shmctl(shm, IPC_RMID, NULL);
            check_err(retcode, "shmctl rm");
            retcode = semctl(sem, 0, IPC_RMID);
            check_err(retcode, "semctl rm");
        }
        else 
            mod_print(shm, sem);
    }
    else
        calculate_mod(shm, sem, argv[2]);
}