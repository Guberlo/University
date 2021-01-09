#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAXLEN 2048

void check_err(int value, char* msg) {
    if(value == -1) {
        perror(msg);
        exit(1);
    }
}

int main(int argc, char** argv) {
    char command[MAXLEN];
    int len, pid;

    if(argc > 1) {
        printf("\033[31;1mERROR: no parameters needed.\033[0m\n");
        exit(1);
    }

    while(1) {
            printf("\033[34;1mEnter a command you want to use (quit to exit): \033[0m\n");
    fgets(command, MAXLEN, stdin);

    len = strlen(command);
    if(command[len - 1] == '\n')
        command[--len] = '\0';

    if(strcmp(command, "quit") == 0)
        break;

    pid = fork();
    check_err(pid, "fork");

    if(pid == 0) {
        execlp(command, command, NULL);
        printf("\033[31;1mError on exec... command: %s\033[0m\n", command);
        exit(1);
    } else // If it's the father wait for child to finish
        wait(NULL);
    }

}