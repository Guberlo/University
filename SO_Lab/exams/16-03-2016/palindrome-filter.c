/**
 * https://diraimondo.dmi.unict.it/wp-content/uploads/classes/so/lab-exams/?get=compito_2016-03-16.pdf
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

#define STRLEN 1024

void check_err(int val, char* msg) {
    if(val == -1) {
        perror(msg);
        exit(1);
    }
}

void check_ptr_err(void* val, char* msg) {
    if(val == NULL) {
        perror(msg);
        exit(1);
    }
}

void read_file(int* pipe_fd, char* filename) {
    int retcode = 0, len;
    int fd;
    char* data_ptr;
    struct stat sb;

    close(pipe_fd[0]);

    if(filename == NULL) {
        filename = malloc(STRLEN);
        retcode = 1; // Flag to check if we've allocated filename
        printf("\033[34;1mInsert input file: \033[0m");
        fgets(filename, STRLEN, stdin);

        len = strlen(filename);
        if(filename[len-1] == '\n');
            filename[--len] = '\0';
    }

    // Check if file is supported
    if(lstat(filename, &sb) == -1 || !S_ISREG(sb.st_mode) || (fd = open(filename, O_RDONLY)) == -1) {
        printf("\033[31;1mERROR: %s is not a regular file\033[0m\n", filename);
        if(retcode == 1)
            free(filename);
        close(pipe_fd[1]);
        exit(1);
    }

    // Map file in memory
    data_ptr = mmap(NULL, sb.st_size, PROT_READ, )
}

int main(int argc, char** argv) {
    int retcode;
    int pipe_r[2], pipe_w[2];

    if(argc != 2) {
        printf("\033[31;1mUSE: %s <input-file>\033[0m\n");
        exit(1);
    }

    // Create pipe to communicate with R
    retcode = pipe(pipe_r);
    check_err(retcode, "pipe");

    // Create pipe to communicate wit W
    retcode = pipe(pipe_w);
    check_err(retcode, "pipe w");

    if(fork() != 0) {
        if(fork() != 0) {
            close(pipe_r[1]);
            wait(NULL);
            close(pipe_r[0]);

            close(pipe_w[0]);
            wait(NULL);
            close(pipe_w[1]);
        }
        else

    }
    else {
        if(argc > 1)
            read_file(pipe_r, argv[1]);
        else
            read_file(pipe_r, NULL);
    }

}