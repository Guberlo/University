/**
 * https://diraimondo.dmi.unict.it/wp-content/uploads/classes/so/lab-exams/?get=compito_2015-07-23.pdf
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAXLEN 1024

typedef struct
{
    long mtype;
    char mtext[MAXLEN];
} msg;

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

void count_letters(char *filename, int queue_fd, int i)
{
    msg mex;
    struct stat statbuf;
    int retcode, fd;
    char *src_data;
    char letters[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    int counters[26] = {0};
    char buffer[MAXLEN];
    char tmp[MAXLEN];

    printf("\033[31;1mChild %d on file %s\033[0m\n", i, filename);

    // Get file stats
    retcode = lstat(filename, &statbuf);
    check_err(retcode, "lstat");

    // Check if it's a regular file
    if (!S_ISREG(statbuf.st_mode))
    {
        printf("\033[31;1mERROR: NOT A REGULAR FILE\033[0m\n");
        exit(1);
    }

    // Open file
    fd = open(filename, O_RDONLY);
    check_err(fd, "open");

    // Map file to space address
    src_data = mmap(NULL, statbuf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    check_ptr_err(src_data, "mmap");

    // Close file
    close(fd);

    // Scan file
    for (int i = 0; i < statbuf.st_size; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (src_data[i] == letters[j])
                counters[j]++;
        }
    }

    for (int i = 0; i < 26; i++)
        printf("\033[34;1m%c:%d ", letters[i], counters[i]);
    printf("\033[0m\n");

    memset(buffer, 0, MAXLEN);
    memset(tmp, 0, MAXLEN);

    for (int i = 0; i < 26; i++)
    {
        sprintf(tmp, "%c:%d ", letters[i], counters[i]);
        strcat(buffer, tmp);
    }

    // SEND MESSAGE
    mex.mtype = 1;
    strncpy(mex.mtext, buffer, MAXLEN);
    retcode = msgsnd(queue_fd, &mex, sizeof(mex), 0);
    check_err(retcode, "msgsnd child");

    // Unmap memory
    retcode = munmap(src_data, statbuf.st_size);
    check_err(retcode, "munmap");

    exit(0);
}

int *extract_count(char *input)
{
    // Split key:value by :
}

int main(int argc, char **argv)
{
    int queue_fd;
    int retcode;
    int counters[26] = {0};
    char key_value[26][30];
    msg mex;

    if (argc < 2)
    {
        printf("\033[31;1mUSE %s <file-1> <file-2> ....\033[0m\n", argv[0]);
        exit(1);
    }

    // Create message queue
    queue_fd = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0660);
    check_err(queue_fd, "msgget");

    for (int i = 1; i < argc; i++)
    {
        if (fork() == 0)
        {
            count_letters(argv[i], queue_fd, i);
        }
        else
        {
            wait(NULL);
            retcode = msgrcv(queue_fd, &mex, sizeof(mex), 0, 0);
            check_err(retcode, "msgrcv father");

            char *res;
            int i = 0;

            // Extract key:value couples
            res = strtok(mex.mtext, " ");
            do
            {
                strcpy(key_value[i++], res);
            } while ((res = strtok(NULL, " ")) != NULL);

            // Extract values from couples
            int tmp;

            for (i = 0; i < 26; i++)
            {
                //printf("\033[36;1m%s\033[0m\n", key_value[i]);
                res = strtok(key_value[i], ":");
                tmp = atoi(strtok(NULL, ":"));
                counters[i] += tmp;
            }
        }
    }

    // Get max
    int max = -1;
    for (int i = 0; i < 26; i++)
    {
        if (counters[i] > max)
            max = counters[i];
    }
    printf("\033[36;1mMAX: %d\033[0m\n", max);

    // Deallocate message queue
    retcode = msgctl(queue_fd, IPC_RMID, NULL);
    check_err(retcode, "msgctl");

    exit(0);
}