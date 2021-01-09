/**
 * One father, two childrens:
 * 
 *  One gets input strings and queues them
 *  The other reads and prints messages from the queue
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define MAXLEN 2048

void check_err(int val, char *msg)
{
    if (val == -1)
    {
        perror(msg);
        msgctl(IPC_PRIVATE, IPC_RMID, NULL);
        exit(1);
    }
}

typedef struct
{
    long mtype;
    char mtext[MAXLEN];
} msg;

void producer(int queue)
{
    msg mex;
    int mex_len, retcode;

    printf("\033[32;1mPRODUCER STARTED\033[0m\n");

    while (strcmp(mex.mtext, "quit") != 0)
    {
        printf("\033[32;1mInsert a message here: \033[0m\n");
        fgets(mex.mtext, MAXLEN, stdin);

        mex_len = strlen(mex.mtext);
        if (mex.mtext[mex_len - 1] == '\n')
            mex.mtext[--mex_len] = '\0';

        mex.mtype = 1;

        retcode = msgsnd(queue, &mex, mex_len + 1, 0);
        check_err(retcode, "msgsnd");

        printf("\033[32;1mMessage sent: %s\033[0m\n", mex.mtext);
    }

    printf("\033[32;1mPRODUCER FINISHED\033[0m\n");
}

void consumer(int queue) {
    msg mex;
    int retcode;

    printf("\033[34;1m\t\t\t\tCONSUMER STARTED\033[0m\n");

    while(strcmp(mex.mtext, "quit") != 0) {
        // Read message
        retcode = msgrcv(queue, &mex, MAXLEN, 0, 0);
        check_err(retcode, "msgrcv");

        printf("\033[34;1m\t\t\t\tMessage received: %s\033[0m\n", mex.mtext);    
    }

    printf("\033[34;1m\t\t\t\tCONSUMER FINISHED\033[0m\n");
}

int main(int argc, char **argv)
{
    int queue_fd, pid;
    msg mex;

    // Create queue
    queue_fd = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0660);
    check_err(queue_fd, "msgget");

    pid = fork();

    if(pid == 0) 
        producer(queue_fd);
    else {
        pid = fork();

        if(pid == 0) 
            consumer(queue_fd);
        else {
            wait(NULL);
            wait(NULL);
        }

        msgctl(queue_fd, IPC_RMID, NULL);
    }
}