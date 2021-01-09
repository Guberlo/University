#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/msg.h>

#define MAXLEN 2048

void check_err(int val, char* msg) {
    if(val == -1) {
        perror(msg);
        exit(1);
    }
}

typedef struct
{
    long mtype;
    char mtext[MAXLEN];
}msg;


int main(int argc, char** argv) {
    int queue_fd, retcode;
    key_t key = 242;
    msg mex;

    // Create queue
    queue_fd = msgget(key, IPC_CREAT | IPC_EXCL | 0660);
    check_err(queue_fd, "msgget");

    // Prepare message
    strncpy(mex.mtext, "HALO SCHWARTZAR", MAXLEN);

    // Set type of message
    mex.mtype = 1;

    // Send message
    retcode = msgsnd(queue_fd, &mex, strlen(mex.mtext) + 1, 0);
    check_err(retcode, "msgsnd");

    // Receive message
    retcode = msgrcv(queue_fd, &mex, sizeof(mex) - sizeof(long), 0, 0);
    check_err(retcode, "msgrcv");

    printf("\033[34;1mMESSAGE RECEIVED: %s\033[0m\n", mex.mtext);

    // Close queue
    retcode = msgctl(queue_fd, IPC_RMID, NULL);
    check_err(retcode, "msgctl");
}
