/**
 * Create and remove a message queue
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>

void check_err(int val, char* msg) {
    if(val == -1) {
        perror(msg);
        exit(1);
    }
}

int main(int argc, char** argv) {
    int queue_fd, retcode;
    struct msqid_ds* buffer;
    key_t key = 234; // Keyo to create queue

    // Create queue
    queue_fd = msgget(key, IPC_CREAT | IPC_EXCL | 0660);
    check_err(queue_fd, "msgget");

    printf("\033[32;1mQueue created: %d\033[0m\n", queue_fd);

    // Close queue
    retcode = msgctl(queue_fd, IPC_RMID, NULL);
    check_err(retcode, "closing queue");
}