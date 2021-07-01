/**
 * https://diraimondo.dmi.unict.it/wp-content/uploads/classes/so/lab-exams/?get=compito_2019-04-23.pdf
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <libgen.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define STRLEN 1024

// Semaphores
#define READER 0
#define REGULAR 1
#define DIRECTORY 2
#define MUTEX 3

typedef struct
{
    char filename[STRLEN];
    int size;
    int completed;
} message;

void check_err(int val, char *msg)
{
    if (val == -1)
    {
        perror(msg);
        exit(1);
    }
}

void check_ptr_err(void *val, char *msg)
{
    if (val == NULL)
    {
        perror(msg);
        exit(1);
    }
}

int WAIT(int sem, int sem_num)
{
    struct sembuf WAIT[1] = {sem_num, -1, 0};
    return semop(sem, WAIT, 1);
}

int SIGNAL(int sem, int sem_num)
{
    struct sembuf SIGNAL[1] = {sem_num, +1, 0};
    return semop(sem, SIGNAL, 1);
}

void reader(message* data_ptr, int sem, char *dirname, int index)
{
    int retcode;
    struct stat sb;
    struct dirent *dir_info;
    char* filepath;
    DIR *dir;

    if (lstat(dirname, &sb) == -1 || !S_ISDIR(sb.st_mode) || (dir = opendir(dirname)) == NULL)
    {
        printf("\033[31;1mERROR: couldn't open directory %s\033[0m\n", dirname);
        exit(1);
    }

    chdir(dirname);

    filepath = malloc(STRLEN);
    while ((dir_info = readdir(dir)))
    {
        if (lstat(dir_info->d_name, &sb) == -1)
        {
            printf("\033[31;1m file %s not supported\033[0m\n", dir_info->d_name);
            continue;
        }

        if (S_ISREG(sb.st_mode))
        {
            WAIT(sem, READER);
            WAIT(sem, MUTEX);
            getcwd(filepath, STRLEN);
            strcat(filepath, "/");
            strcat(filepath, dir_info->d_name);
            strncpy(data_ptr->filename, filepath, STRLEN);
            SIGNAL(sem, MUTEX);
            SIGNAL(sem, REGULAR);
        }
        else if (S_ISDIR(sb.st_mode) && (strcmp(dir_info->d_name, ".") != 0 && strcmp(dir_info->d_name, "..") != 0)) {
            WAIT(sem, READER);
            WAIT(sem, MUTEX);
            strncpy(data_ptr->filename, dir_info->d_name, STRLEN);
            SIGNAL(sem, MUTEX);
            SIGNAL(sem, DIRECTORY);
        }
    }

    chdir("..");

    WAIT(sem, READER);
    data_ptr->completed++;
    strncpy(data_ptr->filename, "EOF", STRLEN);
    SIGNAL(sem, REGULAR);
    SIGNAL(sem, DIRECTORY);

    closedir(dir);
    free(filepath);

    exit(0);
}

void file_consumer(message* data_ptr, int sem, int tot_dirs) {
    int retcode;
    int total_done = 0;
    char* tmp, *dir;
    struct stat sb;

    tmp = malloc(STRLEN);
    while(1) {
        WAIT(sem, REGULAR);
        if(strcmp(data_ptr->filename, "EOF") == 0) {
            total_done++;
            if(total_done == tot_dirs)
                break;
            SIGNAL(sem, READER);
            continue;
        }
        strncpy(tmp, data_ptr->filename, STRLEN);
        dir = dirname(tmp);
        strcat(dir, "/");

        chdir(dir);
        lstat(data_ptr->filename, &sb);

        printf("\033[34;1m%s\t[%dB]\033[0m\n", data_ptr->filename, sb.st_size);
        SIGNAL(sem, READER);
        chdir("..");
    }

    exit(0);
}

void dir_consumer(message* data_ptr, int sem, int tot_dirs) {
    int retcode;
    int total_done = 0;
    struct stat sb;

    while(1) {
        WAIT(sem, DIRECTORY);
        if(strcmp(data_ptr->filename, "EOF") == 0) {
            total_done++;
            if(total_done == tot_dirs)
                break;
            SIGNAL(sem, READER);
            continue;
        }

        printf("\033[34;1m%s\t[directory]\033[0m\n", data_ptr->filename);
        SIGNAL(sem, READER);
    }

    exit(0);
}

int main(int argc, char **argv)
{
    int shm, sem, retcode;
    message* data_ptr;

    if (argc < 2)
    {
        printf("\033[31;1mUSE: %s <dir-1> [dir-2 . . .]\033[0m\n", argv[0]);
        exit(1);
    }

    // Create shm
    shm = shmget(IPC_PRIVATE, sizeof(message), IPC_CREAT | IPC_EXCL | 0660);
    check_err(shm, "shmget");

    // Create sem
    sem = semget(IPC_PRIVATE, 4, IPC_CREAT | IPC_EXCL | 0660);
    check_err(sem, "semget");

    // Init sems
    retcode = semctl(sem, READER, SETVAL, 1);
    check_err(retcode, "semctl");

    retcode = semctl(sem, REGULAR, SETVAL, 0);
    check_err(retcode, "semctl");

    retcode = semctl(sem, DIRECTORY, SETVAL, 0);
    check_err(retcode, "semctl");

    retcode = semctl(sem, MUTEX, SETVAL, 1);
    check_err(retcode, "semctl");

    // Attach to shm
    data_ptr = shmat(shm, NULL, 0);
    check_ptr_err(data_ptr, "shmat");

    data_ptr->completed = 0;

    for (int i = 1; i < argc; i++)
        if (fork() == 0)
            reader(data_ptr, sem, argv[i], i);

    if (fork() == 0)
        file_consumer(data_ptr, sem, argc-1);

    if (fork() == 0)
        dir_consumer(data_ptr, sem, argc-1);

    for(int i=1; i<argc; i++)
        wait(NULL);

    // Deallocate
    retcode = shmctl(shm, IPC_RMID, NULL);
    check_err(retcode, "shmctl");

    retcode = semctl(sem, 0, IPC_RMID);
    check_err(retcode, "semctl");
}