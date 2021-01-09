/**
 * The program can be executed as sender or receiver.
 * The code is in one file just for semplicity.
 * Send a static message.
 * 
 * USE > fifo S: for sender
 * USE > fifo R: for receiver
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAXLEN 2048
#define MAXMSG 29

#define FIFOPATH "/tmp/my-pipe"

void check_err(int val, char* msg) {
    if(val == -1) {
        perror(msg);
        unlink(FIFOPATH);
        exit(1);
    }
}

int main(int argc, char** argv) {
    int retcode, pipefd;
    char buffer[MAXLEN];

    if(argc != 2) {
        printf("\033[31;1mUSE: %s R or S\033[0m\n");
        exit(1);
    }

    // Check if R or S
    if(argv[1][0] == 'S') {
        // Create fifo
        retcode = mkfifo(FIFOPATH, 0700);
        check_err(retcode, "mkfifo");

        // Open fifo
        pipefd = open(FIFOPATH, O_WRONLY);
        check_err(pipefd, "open S");

        // Write into fifo
        for(int i=0; i<MAXMSG; i++) {
            snprintf(buffer, MAXLEN, "msg-%d: STATIC MESSAGE!", i);
            retcode = write(pipefd, buffer, strlen(buffer) + 1);
            check_err(retcode, "write");

            sleep(1); // NECESSARY IN ORDER TO MAKE RECEIVER READ ONLY ONE MESSAGE

            printf("\033[35;1mSent this message: %s\033[0m\n", buffer);
        }
    }
    else if(argv[1][0] == 'R') {
        // Open fifo
        pipefd = open(FIFOPATH, O_RDONLY);
        check_err(pipefd, "open R");

        // Read messages
        for(int i=0; i<MAXMSG; i++) {
            retcode = read(pipefd, buffer, MAXLEN);
            check_err(retcode, "read");

            printf("\033[35;1m>R(%d bytes): %s\033[0m\n", retcode, buffer);
        }

        unlink(FIFOPATH);
        close(pipefd);
    }
}