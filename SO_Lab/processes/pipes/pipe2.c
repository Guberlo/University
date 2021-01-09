#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * Command seq 50 | sort -R
 */

void check_err(int value, char* msg) {
    if(value == -1) {
        perror(msg);
        exit(1);
    }
}

int main(int argc, char** argv) {
    int pipefd[2]; // Pipe vector containing input 0 and output 1
    int retcode, pid;

    retcode = pipe(pipefd);
    check_err(retcode, "pipe");

    pid = fork();

    if(pid == 0) { // Child
        printf("\033[35;1mCHILD STARTED\033[0m\n");
        // Close stdout and set pipe as output
        close(STDOUT_FILENO);
        dup(pipefd[1]);

        // REMEMBER TO CLOSE PIPE STDIN IF NOT NEEDED TO SEND EOF
        close(pipefd[0]);

        // Execute command
        execlp("seq", "seq", "50", NULL);
        perror("execlp child");
        exit(1);
    }
    else {
        printf("\033[35;1mFATHER STARTED\033[0m\n");
        // Close stdin and set pipe as stdin
        close(STDIN_FILENO);
        dup(pipefd[0]);

        // REMEMBER TO CLOSE PIPE OUT IF NOT NEEDED TO SEND EOF
        close(pipefd[1]);

        // Execute command
        execlp("sort", "sort", "-R", NULL);
        perror("execlp father");
        exit(1);
    }
}