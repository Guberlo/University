/**
 * https://diraimondo.dmi.unict.it/wp-content/uploads/classes/so/lab-exams/?get=compito_2020-07-30.pdf
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define MAX_LEN 64
#define MAX_FILE_LEN 1024

#define R_EMPTY 0
#define R_FULL 1
#define W_EMPTY 2
#define W_FULL 3
#define MUTEX 4

#define EOF_STR "!!_EOF_!!"

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

void reader(int shm, int sem, char* filename) {
    int len, retcode;
    char* data_ptr, *line;
    struct stat sb;
    FILE* file;

    if(lstat(filename, &sb) == -1 || !S_ISREG(sb.st_mode) || (file = fopen(filename, "r")) == NULL) {
        printf("\033[31;1mERROR: file not supported\033[0m\n");
        exit(1);
    }

    // Attach to shm
    data_ptr = shmat(shm, NULL, 0);
    check_ptr_err(data_ptr, "shmat");

    line = malloc(MAX_LEN);
    while(fgets(line, MAX_LEN, file)) {
        len = strlen(line);

        if(line[len-1] == '\n')
            line[--len] = '\0';

        // Insert row into SHM
        WAIT(sem, R_EMPTY);
        WAIT(sem, MUTEX);
        strncpy(data_ptr, line, MAX_LEN);
        SIGNAL(sem, MUTEX);
        SIGNAL(sem, R_FULL);
    }

    // Send EOF
    WAIT(sem, R_EMPTY);
    WAIT(sem, MUTEX);
    strncpy(data_ptr, EOF_STR, MAX_LEN);
    SIGNAL(sem, MUTEX);
    SIGNAL(sem, R_FULL);

    fclose(file);
    free(line);
    exit(0);
}

void palindrome_check(int shm, int sem) {
    int len, index, retcode;
    char eof_flag = 0, pal_flag;
    char* data_ptr, *line;

    // Attach to shm
    data_ptr = shmat(shm, NULL, 0);
    check_ptr_err(data_ptr, "shmat");

    line = malloc(MAX_LEN);
    while(!eof_flag) {
        WAIT(sem, R_FULL);
        WAIT(sem, MUTEX);

        strncpy(line, data_ptr, MAX_LEN);

        if(strcmp(line, EOF_STR) == 0)
            eof_flag = 1;
        
        // Check if it is palindrome
        pal_flag = 0;
        len = strlen(line);
        for(int i=0; i<len/2; i++) {
            index = (len-1) - i;
            if(tolower(line[i]) == tolower(line[index]))
                pal_flag = 1;
            else {
                pal_flag = 0;
                break;
            }
        }

        if(pal_flag || eof_flag) {
            // Write to shm
            WAIT(sem, W_EMPTY);
            strncpy(data_ptr, line, MAX_LEN);
            SIGNAL(sem, W_FULL);
        }
        else {
            SIGNAL(sem, MUTEX);
            SIGNAL(sem, R_EMPTY);
        }
        
    }

    free(line);
}

void writer(int shm, int sem, char* filename) {
    int len, retcode;
    char* data_ptr, *line;
    struct stat sb;
    FILE* file;

    if(lstat(filename, &sb) == -1 || !S_ISREG(sb.st_mode) || (file = fopen(filename, "w")) == NULL) {
        printf("\033[31;1mERROR: file not supported\033[0m\n");
        exit(1);
    }

    // Attacch to shm
    data_ptr = shmat(shm, NULL, 0);
    check_ptr_err(data_ptr, "shmat");

    line = malloc(MAX_LEN);
    while(1) {
        WAIT(sem, W_FULL);

        strncpy(line, data_ptr, MAX_LEN);
        if(strcmp(line, EOF_STR) == 0)
            break;

        printf("\033[33;1m%s\033[0m\n", line);
        SIGNAL(sem, MUTEX);
        SIGNAL(sem, W_EMPTY);
        SIGNAL(sem, R_EMPTY);
    }

    free(line);
    fclose(file);
    exit(0);
}

int main(int argc, char** argv) {
    int shm, sem, len, retcode;
    char file_in[MAX_FILE_LEN];
    char file_out[MAX_FILE_LEN];

    if(argc > 3) {
        printf("\033[31;1mUSE: %s  [input-file] [output-file]\033[0m\n", argv[0]);
        exit(1);
    }

    // Create shm
    shm = shmget(IPC_PRIVATE, MAX_LEN, IPC_CREAT | IPC_EXCL | 0660);
    check_err(shm, "shmget");

    // Create sem
    sem = semget(IPC_PRIVATE, 5, IPC_CREAT | IPC_EXCL | 0660);
    check_err(sem, "semget");

    // Init sem
    semctl(sem, R_EMPTY, SETVAL, 1);
    semctl(sem, R_FULL, SETVAL, 0);

    semctl(sem, W_EMPTY, SETVAL, 1);
    semctl(sem, W_FULL, SETVAL, 0);

    semctl(sem, MUTEX, SETVAL, 1);

    if(argc > 1) 
        strncpy(file_in, argv[1], MAX_FILE_LEN);
    else {
        printf("\033[34;1mInsert input filename: \033[0m");
        fgets(file_in, MAX_FILE_LEN, stdin);

        len = strlen(file_in);
        if(file_in[len-1] == '\n')
            file_in[--len] = '\0';
    }

    if(argc > 2) 
        strncpy(file_out, argv[2], MAX_FILE_LEN);
    else {
        printf("\033[34;1mInsert input filename: \033[0m");
        fgets(file_out, MAX_FILE_LEN, stdin);

        len = strlen(file_out);
        if(file_out[len-1] == '\n')
            file_out[--len] = '\0';
    }

    if(fork() != 0) {
        if(fork() != 0) {
            palindrome_check(shm, sem);
            wait(NULL);
            wait(NULL);

            // Deallocate shared memory and sem
            retcode = shmctl(shm, IPC_RMID, NULL);
            check_err(retcode, "shmctl");

            retcode = semctl(sem, 0, IPC_RMID);
            check_err(retcode, "semctl");
        }
        else 
            writer(shm, sem, file_out);
    }
    else 
        reader(shm, sem, file_in);
}