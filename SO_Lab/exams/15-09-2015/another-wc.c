/**
 * Insert link
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define SHMLEN 2
#define STRLEN 1024

#define SEM_READ 0
#define SEM_WRITE 1

void check_err(int val, char* msg) {
    if(val == -1) {
        perror(msg);
        exit(1);
    }
}

void check_shm_err(char* val, char* msg) {
    if(val == (char*) -1) {
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

void read_file(int shm, int sem, char* filename) {
    int len, retcode, fd;
    char text[STRLEN];
    char* data_ptr;
    char c;

    if(filename == NULL) {
        printf("\033[36;1mInsert a filename: \033[0m");
        fgets(text, STRLEN, stdin);

        len = strlen(text);
        if(text[len-1] == '\n')
            text[--len] = '\0';
        
        printf("filename: %s\n", text);
    }

    // Attach to shm
    data_ptr = shmat(shm, NULL, 0);
    check_shm_err(data_ptr, "shmat");

    // Open file
    fd = open(filename, O_RDONLY);
    check_err(fd, "open");

    // Read one byte at a time
    while(1) {
        WAIT(sem, SEM_READ);
        if((retcode = read(fd, &c, 1)) > 0) {
            *data_ptr = c;
        }
        else {
            check_err(retcode, "READ");
            strncpy(data_ptr, "!!", SHMLEN);
            SIGNAL(sem, SEM_WRITE);
            break;
        }
        SIGNAL(sem, SEM_WRITE);
    }
    exit(0);
}

int is_word(char c) {
    switch (c) {
        case ' ':
            return 1;
        case '\t':
            return 1;
        case '.':
            return 1;
        case ',':
            return 1;
        case ';':
            return 1;
        case ':':
            return 1;
        case '!':
            return 1;
        case '?':
            return 1;
        default:
            return 0;
    }
}

int is_row(char c) {
    return c == '\n';
}

void wc(int shm, int sem) {
    char* data_ptr;
    char prev = '\0';
    int rows = 0, words = 0, chars = 0;

    // Attach to shm
    data_ptr = shmat(shm, NULL, 0);
    check_shm_err(data_ptr, "shmat father");

    while(1) {
        WAIT(sem, SEM_WRITE);

        // Check if we read all file
        if(strlen(data_ptr) > 1) {
            printf("\033[31;1mEOF\033[0m\n");
            break;
        }
        
        chars++;
        if(is_row(*data_ptr))
            rows++;
        else if(is_word(*data_ptr) && !is_word(prev))
            words++;
        
        prev = *data_ptr;
        SIGNAL(sem, SEM_READ);
    }

    printf("\033[33;1mchars: %d\twords: %d\trows: %d\033[0m\n", chars, words, rows);
}

int main(int argc, char** argv) {
    int shm, sem, retcode;

    if(argc > 2) {
        printf("\033[31;1mUSE: %s [text-file]\033[0m\n", argv[0]);
        exit(1);
    }

    // Create shm
    shm = shmget(IPC_PRIVATE, SHMLEN, IPC_CREAT | IPC_EXCL | 0660);
    check_err(shm, "shmget");

    // Create sem
    sem = semget(IPC_PRIVATE, 2, IPC_CREAT | IPC_EXCL | 0660);
    check_err(sem, "semget");

    // Init sem
    retcode = semctl(sem, SEM_READ, SETVAL, 1);
    check_err(retcode, "semctl");

    retcode = semctl(sem, SEM_WRITE, SETVAL, 0);
    check_err(retcode, "semctl");

    if(fork() == 0) {
        if(argc == 2)
            read_file(shm, sem, argv[1]);
        else
            read_file(shm, sem, NULL);
    }
    else {
        wc(shm, sem);
    }

    // Deallocate shm
    retcode = shmctl(shm, IPC_RMID, NULL);
    check_err(retcode, "shmctl");

    // Deallocate sem
    retcode = semctl(sem, 1, IPC_RMID);
    check_err(retcode, "semctl");
}