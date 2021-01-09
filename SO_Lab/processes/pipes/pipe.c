#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAXLEN 2048

void check_err(int value, char* msg) {
    if(value == -1) {
        perror(msg);
        exit(1);
    }
}

int main(int argc, char** argv) {
    int pipefd[2];
    int retcode, pid;
    char buffer[MAXLEN];

    // Create pipe
    retcode = pipe(pipefd);
    check_err(retcode, "pipe");

    pid = fork();
    check_err(pid, "fork");

    if(pid == 0) {
        retcode = read(pipefd[0], buffer, MAXLEN);
        check_err(retcode, "read child");

        printf("\033[34;1mChild heard: %s\033[0m\n", buffer);

        strncpy(buffer, "C SPACCHIAMO DI SMEEESH", MAXLEN);
        retcode = write(pipefd[1], buffer, strlen(buffer) + 1);
        check_err(retcode, "write child");

        printf("\033[34;1mChild said: %s\033[0m\n",buffer);
    }
    else {
        // Father writes to buffer and sends
        strncpy(buffer, "AINIZIO LA SERATA IIIIIIHIHI", MAXLEN);
        retcode = write(pipefd[1], buffer, strlen(buffer) + 1);
        check_err(retcode, "write father");

        printf("\033[35;1mFather said: %s\033[0m\n", buffer);

        // sleep and then read
        sleep(1);

        retcode = read(pipefd[0], buffer, MAXLEN);
        check_err(retcode, "read father");

        printf("\033[35;1mFather heard: %s\033[0m\n", buffer);
    }
}