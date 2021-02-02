/**
 * https://diraimondo.dmi.unict.it/wp-content/uploads/classes/so/lab-exams/?get=compito_2019-09-13.pdf
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define MAX_LEN 1024
#define QUIT_STR "YABROEXIIIIIIIIIT"

#define SCANNER 0
#define STATER 1
#define FATHER 2

typedef struct {
    char filename[MAX_LEN];
    char id;
    char n_completed;
    int n_blocks;
} message;

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


void scan_directory(int sem, char* filename, message* data_ptr, int id) {
    int retcode;
    struct stat sb;
    struct dirent* dir_info;
    DIR* dir;

    if(lstat(filename, &sb) == -1 || !S_ISDIR(sb.st_mode) || (dir = opendir(filename)) == NULL) {
        printf("\033[31;1mERROR: file is not supported\033[0m\n");
        // SIGNAL OTHERS TO CLOSE ??
        exit(1);
    }

    chdir(filename);

    while( (dir_info = readdir(dir)) ) {
        retcode = lstat(dir_info->d_name, &sb);
        check_err(retcode, "lstat dir");

        if(S_ISREG(sb.st_mode)) {
            WAIT(sem, SCANNER);
            getcwd(data_ptr->filename, MAX_LEN);
            strcat(data_ptr->filename, "/");
            strncat(data_ptr->filename, dir_info->d_name, MAX_LEN);
            data_ptr->id = id;
            printf("\033[33;1mSCANNER%d: %s\033[0m\n", id, data_ptr->filename);
            SIGNAL(sem, STATER);
        }
        else if(S_ISDIR(sb.st_mode)) {
            if(strcmp(dir_info->d_name, ".") == 0 || strcmp(dir_info->d_name, "..") == 0)
                continue;
            else
                scan_directory(sem, dir_info->d_name, data_ptr, id);
        }
    }
    // SIGNAL TO FINISH TO STATER
    WAIT(sem, SCANNER);
    strncpy(data_ptr->filename, QUIT_STR, MAX_LEN);
    SIGNAL(sem, STATER);

    chdir("..");
    closedir(dir);
    exit(0);
}

void scanner(int shm, int sem, char* filename, int id) {
    int retcode;
    struct stat sb;
    struct dirent* dir_info;
    DIR* dir;
    message* data_ptr;

    // Attach to shm
    data_ptr = shmat(shm, NULL, 0);
    check_ptr_err(data_ptr, "shmat");

    scan_directory(sem, filename, data_ptr, id);

    exit(0);
}

void stater(int shm, int sem, int n_dirs) {
    int retcode, scanners = n_dirs;
    struct stat sb;
    message* data_ptr;

    // Attach to shm
    data_ptr = shmat(shm, NULL, 0);
    check_ptr_err(data_ptr, "shmat");

    // NEED TO CHECK FOR A CONDITION TO STOP
    while(scanners > 0) {
        WAIT(sem, STATER);
        if(strncmp(data_ptr->filename, QUIT_STR, MAX_LEN) == 0) 
            scanners--;
        else {
            retcode = lstat(data_ptr->filename, &sb);
            check_err(retcode, data_ptr->filename);

            data_ptr->n_blocks = sb.st_blocks;
            printf("\033[34;1mSTATER: %s\t%d\033[0m\n", data_ptr->filename, sb.st_blocks);
        }
        SIGNAL(sem, FATHER);
    }

    WAIT(sem, STATER);
    strncpy(data_ptr->filename, QUIT_STR, MAX_LEN);
    SIGNAL(sem, FATHER);

    exit(0);
}

void count_blocks(int shm, int sem, int* count, int n_dirs) {
    int index;
    message* data_ptr;

    // Attach to shm
    data_ptr = shmat(shm, NULL, 0);
    check_ptr_err(data_ptr, "shmat");

    data_ptr->n_completed = 0;

    while(1) { // CHECK FOR A CONDITION TO FINISH
        WAIT(sem, FATHER);
        if(strcmp(data_ptr->filename, QUIT_STR) == 0)
            break;
        index = data_ptr->id;
        count[index] += data_ptr->n_blocks;
        printf("\033[35;1mCOUNT: count[%d] = %d\033[0m\n", index, count[index]);
        SIGNAL(sem, SCANNER);
    }

}

int main(int argc, char** argv) {
    int shm, sem, retcode;
    char dirname[MAX_LEN];
    int count[argc];

    // Create shm
    shm = shmget(IPC_PRIVATE, sizeof(message), IPC_CREAT | IPC_EXCL | 0660);
    check_err(shm, "shmget");

    // Create sem
    sem = semget(IPC_PRIVATE, 3, IPC_CREAT | IPC_EXCL | 0660);
    check_err(sem, "semget");

    // Init sems
    retcode = semctl(sem, SCANNER, SETVAL, 1);
    check_err(retcode, "semctl");

    retcode = semctl(sem, STATER, SETVAL, 0);
    check_err(retcode, "semctl");

    retcode = semctl(sem, FATHER, SETVAL, 0);
    check_err(retcode, "semctl");

    // Init count array to 0
    for(int i=0; i<argc; i++)
        count[i] = 0;

    if(fork() == 0)
        stater(shm, sem, argc-1);

    if(argc == 1) {
        strncpy(dirname, ".", 1);
    }
    else {
        for(int i=1; i<argc; i++) {
            if(fork() == 0) {
                strncpy(dirname, argv[i], MAX_LEN);
                scanner(shm, sem, dirname, i);
            }
        }
    }

    count_blocks(shm, sem, count, argc-1);

    for(int i=1; i<argc; i++)
        printf("\033[34;1m%d\t%s\033[0m\n", count[i], argv[i]);

    // Deallocate
    retcode = shmctl(shm, IPC_RMID, NULL);
    check_err(retcode, "shmctl");

    retcode = semctl(sem, 0, IPC_RMID);
    check_err(retcode, "semctl");
}