/**
 * https://diraimondo.dmi.unict.it/wp-content/uploads/classes/so/lab-exams/?get=compito_2016-07-13.pdf
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

#define STRLEN 1024
#define FIFO_PATH "/tmp/my_pipe_%d.txt"

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

void writer(int* pipe_fd, char* named_pipe) {
    FILE* file;
    char* line;
    int len;

    printf("\033[34;1m\t\t\tWRITER START\033[0m\n");
    // Close unused channels
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    
    // Open stream from named pipe
    file = fopen(named_pipe, "r");
    check_ptr_err(file, "fdopen writer");

    line = malloc(STRLEN);
    while(fgets(line, STRLEN, file)) {
        if(line[len-1] == '\n')
            line[--len] = '\0';
        printf("\t\t\t\033[34;1mfound: %s\033[0m\n", line);
    }
    
    printf("\t\t\t\033[34;1mWRITER EXIT\033[0m\n");
    fclose(file);
    exit(0);
}

void filter(int case_sensitive, int inverse, char* named_pipe, int* pipe_fd, char* tosearch) {
    FILE* file_in, *file_out;
    char* line;
    int flag, len, retcode;
    struct stat sb;

    printf("\033[35;1m\tFILTERER START\033[0m\n");
    // Close unused channels
    close(pipe_fd[1]);

    // Open stream from pipe
    file_in = fdopen(pipe_fd[0], "r");
    check_ptr_err(file_in, "fdopen filter");

    // Open stream from named pipe
    file_out = fopen(named_pipe, "w");
    check_ptr_err(file_out, "fdopen filter");

    line = malloc(STRLEN);
    while(fgets(line, STRLEN, file_in)) {
        len = strlen(line);

        if(line[len-1] == '\n')
            line[--len] = '\0';
        
        if(case_sensitive)
            flag = (strstr(line, tosearch) != NULL);
        else
            flag = (strcasestr(line, tosearch) != NULL);

        if((inverse && !flag) || (!inverse && flag)) {
            strcat(line, "\n");
            fputs(line, file_out);
        }
    }

    close(pipe_fd[0]);
    free(line);
    fclose(file_in);
    fclose(file_out);
    printf("\033[35;1m\tFILTERER FINISHED\033[0m\n");
}

void reader(char* filename, int* pipe_fd) {
    int retcode = 0, len;
    char* line;
    struct stat sb;
    FILE* file_in, *file_out;

    // Close unused channel
    close(pipe_fd[0]);

    printf("\033[33;1mSTART\033[0m\n");
    if(filename == NULL) {
        filename = malloc(STRLEN);
        retcode = 1;
        printf("\033[36;1mInsert input file: \033[0m");
        fgets(filename, STRLEN, stdin);
        len = strlen(filename);

        if(filename[len-1] == '\n')
            filename[--len] = '\0';
    }

    file_in = fopen(filename, "r");
    check_ptr_err(file_in, "fopen");

    file_out = fdopen(pipe_fd[1], "w");
    check_ptr_err(file_out, "fopen");

    line = malloc(STRLEN);
    while(fgets(line, STRLEN, file_in)) {
        fputs(line, file_out);
    }

    free(line);
    fclose(file_in);
    fclose(file_out);
    close(pipe_fd[1]);

    printf("\033[33;1mFINISHED\033[0m\n");
    exit(0);
}

int main(int argc, char** argv) {
    int pipe_fd[2];
    int retcode, case_sensitive = 1, inverse = 0;
    char* tosearch = NULL;
    char* filename = NULL;
    char fifo_path[STRLEN];
    struct stat sb;

    // Check what parameter has been passed
    for(int i=1; i<argc; i++) {
        if(strcmp(argv[i], "-v") == 0)
            case_sensitive = 0;
        else if(strcmp(argv[i], "-i") == 0)
            inverse = 1;
        else if(strlen(argv[i]) > 0) {
            if(tosearch == NULL)
                tosearch = argv[i];
            else {
                if(lstat(argv[i], &sb) == 0 && S_ISREG(sb.st_mode))
                    filename = argv[i];
                else {
                    printf("\033[31;1mERROR: file %s not supported\033[0m\n", filename);
                    exit(1);
                }
            }
        }
    }

    if(argc < 2) {
        printf("\033[31;1mUSE: %s [-i] [-v] <word> [file]\033[0m\n", argv[0]);
        exit(1);
    }

    // Create pipe
    retcode = pipe(pipe_fd);
    check_err(retcode, "pipe");

    // Create named pipe
    snprintf(fifo_path, STRLEN, FIFO_PATH, getpid());
    retcode = mkfifo(fifo_path, 0600);
    check_err(retcode, "mkfifo");
    
    if(fork() != 0) {
        if(fork() != 0) {
            if(fork() != 0) {
                close(pipe_fd[0]);
                close(pipe_fd[1]);
                wait(NULL);
                wait(NULL);
                wait(NULL);

                unlink(fifo_path);
            }
            else
                writer(pipe_fd, fifo_path);
        }
        else
            filter(case_sensitive, inverse, fifo_path, pipe_fd, tosearch);
    }
    else
        reader(filename, pipe_fd);
        
}