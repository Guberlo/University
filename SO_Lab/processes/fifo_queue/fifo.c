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
#include <sys/stat.h>
#include <sys/types.h>

#define MAXLEN 2048
#define FIFOPATH "/tmp/my-pipe"
#define MSGNUM 20

void check_err(int value, char* msg) {
    if(value == -1) {
        perror(msg);
        exit(1);
    }
}

int main(int argc, char** argv) {
    int retcode, pipefd;
    char* message = "THIS IS A MESSAGE!";
    char buffer[MAXLEN];

    if(argc != 2) {
        printf("\033[31;1mUSE: %s S or R\033[0m\n", argv[0]);
        exit(1);
    }

    // Check if the program is launched as sender or receiver
    if(argv[1][0] == 'S') {
        // Create named pipe
        retcode = mkfifo(FIFOPATH, 0600);
        check_err(retcode, "mkfifo");

        // Open pipe to write data
        pipefd = open(FIFOPATH, O_WRONLY);
        check_err(pipefd, "open");

        for(int i=0; i<MSGNUM; i++) {
            retcode = write(pipefd, message, strlen(message) + 1);
            check_err(retcode, "write");

            printf("\033[35;1mMessage sent: %s\033[0m\n", message);
        }
    }
    else if(argv[1][0] == 'R') {
        // No need to create the pipe since it has been already created

        pipefd = open(FIFOPATH, O_RDONLY);
        check_err(pipefd, "open");

        // Read data
        for(int i=0; i<MSGNUM; i++) {
            retcode = read(pipefd, buffer, strlen(message) + 1);
            check_err(retcode, "read");

            printf("\033[34;1mMessage received(%d): %s\033[0m\n", retcode, buffer);
        }

        unlink(FIFOPATH);
    }
    else {
        printf("\033[31;1mUSE: %s S or R\033[0m\n", argv[0]);
        exit(1);
    }
}