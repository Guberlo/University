/**
 * https://diraimondo.dmi.unict.it/wp-content/uploads/classes/so/lab-exams/?get=compito_2020-12-15.pdf
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/mman.h>

#define STRLEN 1024

#define DB 0
#define EMPTY 1
#define MUTEX 2
#define OUT_EMPTY 3
#define OUT_FULL 4

#define EOF_FILE "!!:::EOF:::!!"

typedef struct {
    char pid;
    char name[STRLEN];
    int value;
} db_message;

typedef struct {
    char id;
    char line[STRLEN];
} in_message;

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

void in(int shm, int sem, char* filename, int id) {
    int retcode, len;
    char* line;
    struct stat sb;
    FILE* file;
    in_message* message;

    if(lstat(filename, &sb) == -1 || !S_ISREG(sb.st_mode) || (file = fopen(filename, "r")) == NULL) {
        printf("\033[31;1mERROR: file %s not supported\033[0m\n", filename);
        exit(1);
    }

    // Attach to shm
    message = shmat(shm, NULL, 0);
    check_ptr_err(message, "shmat");

    line = malloc(STRLEN);
    while(fgets(line, STRLEN, file)) {
        len = strlen(line);
        if(line[len-1] == '\n')
            line[--len] = '\0';

        WAIT(sem, EMPTY);
        WAIT(sem, MUTEX);

        printf("\033[33mIN%d: sending query %s\033[0m\n", id, line);
        message->id = id;
        strncpy(message->line, line, STRLEN);

        SIGNAL(sem, MUTEX);
        SIGNAL(sem, DB);
        
    }

    // Send eof
    WAIT(sem, EMPTY);
    WAIT(sem, MUTEX);

    message->id = id;
    strncpy(message->line, EOF_FILE, STRLEN);

    SIGNAL(sem, MUTEX);
    SIGNAL(sem, DB);

    exit(0);
}

void db(int shm_in, int shm_out, int sem, char* filename) {
    int retcode, len, fd, completed = 0;
    char* line, *file_ptr, *token, *tmp;
    char* name, *value;
    struct stat sb;
    db_message* message;
    in_message* input;

    if(lstat(filename, &sb) == -1 || !S_ISREG(sb.st_mode) || (fd = open(filename, O_RDONLY)) == -1) {
        printf("\033[31;1mERROR: file %s not supported\033[0m\n", filename);
        exit(1);
    }

    // Attach to both shm
    input = shmat(shm_in, NULL, 0);
    check_ptr_err(input, "shmat");

    message = shmat(shm_out, NULL, 0);
    check_ptr_err(message, "shmat");

    // Save file in RAM
    file_ptr = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    check_ptr_err(file_ptr, "mmap");

    tmp = malloc(STRLEN);
    // name = malloc(STRLEN/2);
    // value = malloc(STRLEN/2);
    while(1) {
        WAIT(sem, DB);
        WAIT(sem, MUTEX);

        if(strncmp(input->line, EOF_FILE, sizeof(EOF_FILE)) == 0) {
            completed++;
            if(completed == 2)
                break;
            
            SIGNAL(sem, MUTEX);
            SIGNAL(sem, EMPTY);
            continue;
        }


        if( (token = strstr(file_ptr, input->line)) ) {
            strncpy(tmp, token, STRLEN);
            strtok(tmp, "\n");
            name = strtok(tmp, ":");
            value = strtok(NULL, ":");
            printf("\033[36mDB: query %s from IN%d found with value %d\033[0m\n", tmp, input->id, atoi(value));

            WAIT(sem, OUT_EMPTY);

            message->pid = input->id;
            strncpy(message->name, name, sizeof(name));
            message->value = atoi(value);

            SIGNAL(sem, OUT_FULL);
        }

        SIGNAL(sem, MUTEX);
        SIGNAL(sem, EMPTY);
    }

    // Send EOF to OUT
    WAIT(sem, OUT_EMPTY);

    message->pid = -1;

    SIGNAL(sem, OUT_FULL);

    free(tmp);
    // free(name);
    // free(value);
    exit(0);
}

void out(int shm, int sem) {
    db_message* message;
    int count[2] = {0};
    int sum[2] = {0};

    // Attach to shm
    message = shmat(shm, NULL, 0);
    check_ptr_err(message, "shmat");

    while(1) {
        WAIT(sem, OUT_FULL);

        if(message->pid == -1)
            break;

        count[message->pid-1]++;
        sum[message->pid-1] += message->value;

        SIGNAL(sem, OUT_EMPTY);
    }

    printf("\n\033[35mOUT: received n.%d values with total %d for IN1\033[0m\n", count[0], sum[0]);
    printf("\033[35mOUT: received n.%d values with total %d for IN2\033[0m\n", count[1], sum[1]);
    exit(0);
}

int main(int argc, char** argv) {
    int retcode, shm1, shm2, sem;
    int key1, key2;
    if(argc < 4) {
        printf("\033[31;1mUSE: %s <db-file> <query-file-1> <query-file-2>\033[0m\n", argv[0]);
        exit(1);
    }

    key1 = ftok(argv[1], 0);
    key2 = ftok(argv[2], 0);

    // Create IN1-IN2-DB segment: contains a query string max STRLEN
    shm1 = shmget(key1, STRLEN, IPC_CREAT | IPC_EXCL | 0660);
    check_err(shm1, "shmget");

    // Create DB-OUT segment: contains a db_message
    shm2 = shmget(key2, sizeof(db_message), IPC_CREAT | IPC_EXCL | 0660);
    check_err(shm2, "shmget2");

    // Create sems
    sem = semget(IPC_PRIVATE, 5, IPC_CREAT | IPC_EXCL | 0660);
    check_err(sem, "semget");

    // Init sems
    retcode = semctl(sem, DB, SETVAL, 0);
    check_err(retcode, "semctl");

    retcode = semctl(sem, EMPTY, SETVAL, 1);
    check_err(retcode, "semctl");

    retcode = semctl(sem, MUTEX, SETVAL, 1);
    check_err(retcode, "semctl");

    retcode = semctl(sem, OUT_EMPTY, SETVAL, 1);
    check_err(retcode, "semctl");

    retcode = semctl(sem, OUT_FULL, SETVAL, 0);
    check_err(retcode, "semctl");

    if(fork() != 0) {
        if(fork() != 0) {
            if(fork() != 0) {
                if(fork() != 0) {
                    wait(NULL);
                    wait(NULL);
                    wait(NULL);
                    wait(NULL);

                    // Deallocate
                    retcode = shmctl(shm1, IPC_RMID, NULL);
                    check_err(retcode, "shmctl");

                    retcode = shmctl(shm2, IPC_RMID, NULL);
                    check_err(retcode, "shmctl2");

                }
                else
                    out(shm2, sem);
            }
            else
                db(shm1, shm2, sem, argv[1]);
        }
        else
            in(shm1, sem, argv[3], 2); // IN2
    }
    else
        in(shm1, sem, argv[2], 1); // IN1
}