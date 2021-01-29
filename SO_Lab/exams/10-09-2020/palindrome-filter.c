/**
 * https://diraimondo.dmi.unict.it/wp-content/uploads/classes/so/lab-exams/?get=compito_2020-09-10.pdf
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define STRLEN 1024

void check_err(int val, char* msg) {
    if(val == -1) {
        perror(msg);
        exit(1);
    }
}

void reader(int* p_fd, char* filename) {
    int len, retcode;
    char* line;
    struct stat sb;
    FILE* file_in, *file_out;

    close(p_fd[0]);

    if(lstat(filename, &sb) == 1 || !S_ISREG(sb.st_mode) || (file_in = fopen(filename, "r")) == NULL) {
        printf("\033[31;1mERROR: file not supported\033[0m\n");
        exit(1);
    }

    file_out = fdopen(p_fd[1], "w");

    line = malloc(STRLEN);
    while(fgets(line, STRLEN, file_in)) {
        len = strlen(line);

        retcode = fputs(line, file_out);
        check_err(retcode, "fputs");
    }

    fclose(file_in);
    fclose(file_out);
    close(p_fd[1]);
    exit(0);
}

void palindrome_check(int fd_in, int fd_out) {
    int retcode, len, index;
    char* line;
    char flag = 0;
    FILE* file_in, *file_out;

    file_in = fdopen(fd_in, "r");
    file_out = fdopen(fd_out, "w");

    line = malloc(STRLEN);
    while(fgets(line, STRLEN, file_in)) {
        len = strlen(line);

        if(line[len-1] == '\n')
            line[--len] = '\0';

        for(int i=0; i<len/2; i++) {
            index = (len-1) - i;
            if(line[i] == line[index]) {
                flag = 1;
            }
            else {
                flag = 0;
                break;
            }
        }

        if(flag == 1) {
            strcat(line, "\n");
            retcode = fputs(line, file_out);
            check_err(retcode, "fputs");
        }
    }

    fclose(file_in);
    fclose(file_out);
}

void writer(int* p_fd) {
    int retcode;
    char* line;
    FILE* file;

    close(p_fd[1]);

    file = fdopen(p_fd[0], "r");

    line = malloc(STRLEN);
    while(fgets(line, STRLEN, file)) {
        printf("\033[36;1m%s\033[0m", line);
    }

    fclose(file);
    close(p_fd[0]);
    exit(0);
}

int main(int argc, char** argv) {
    int retcode;
    int pr_fd[2];
    int pw_fd[2];

    if(argc != 2) {
        printf("\033[31;1mUSE: %s <file-name>\033[0m\n", argv[0]);
        exit(1);
    }

    // Create first pipe
    retcode = pipe(pr_fd);
    check_err(retcode, "pipe r");

    // Create second pipe
    retcode = pipe(pw_fd);
    check_err(retcode, "pipe w");

    if(fork() != 0) {
        if(fork() != 0) {
            wait(NULL);
            close(pr_fd[1]);
            // Read from pipe and send
            palindrome_check(pr_fd[0], pw_fd[1]);
            close(pr_fd[0]);
            close(pw_fd[0]);
            close(pw_fd[1]);
            wait(NULL);
        }
        else {
            close(pr_fd[0]);
            close(pr_fd[1]);
            writer(pw_fd);
        }
    }
    else {
        close(pw_fd[0]);
        close(pw_fd[1]);
        reader(pr_fd, argv[1]);
    }
}