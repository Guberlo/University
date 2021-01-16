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

void check_err(int val, char *msg)
{
    if (val == -1)
    {
        perror(msg);
        exit(1);
    }
}

void check_ptr_err(void *val, char *msg)
{
    if (val == NULL)
    {
        perror(msg);
        exit(1);
    }
}

void read_file(int *pipe_fd, char *filename)
{
    int retcode = 0, len;
    int fd;
    char *data_ptr, *line;
    struct stat sb;

    close(pipe_fd[0]);

    if (filename == NULL)
    {
        filename = malloc(STRLEN);
        retcode = 1; // Flag to check if we've allocated filename
        printf("\033[34;1mInsert input file: \033[0m");
        fgets(filename, STRLEN, stdin);

        len = strlen(filename);
        if (filename[len - 1] == '\n')
            ;
        filename[--len] = '\0';
    }

    // Check if file is supported
    if (lstat(filename, &sb) == -1 || !S_ISREG(sb.st_mode) || (fd = open(filename, O_RDONLY)) == -1)
    {
        printf("\033[31;1mERROR: %s is not a regular file\033[0m\n", filename);
        if (retcode == 1)
            free(filename);
        close(pipe_fd[1]);
        exit(1);
    }

    // Map file in memory
    data_ptr = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
    check_ptr_err(data_ptr, "mmap");

    // Get each line
    line = malloc(STRLEN);
    strncpy(line, data_ptr, STRLEN);

    line = strtok(line, " ");
    do
    {
        retcode = write(pipe_fd[1], line, STRLEN);
        check_err(retcode, "write");
    } while ((line = strtok(NULL, "\n")) != NULL);

    free(line);
    close(fd);
    close(pipe_fd[1]);
}

void check_palindrome(int* pipe_r, int* pipe_w)
{
    int len, retcode;
    int flag, tmp;
    char* line;
    FILE* file_r, *file_w;

    // Get stream from pipe_r
    file_r = fdopen(pipe_r[0], "r");
    check_ptr_err(file_r, "fdopen r");

    // Get stream from pipe_w
    file_w = fdopen(pipe_w[1], "w");
    check_ptr_err(file_w, "fdopen w");

    // Get each line
    line = malloc(STRLEN);
    while((line = fgets(line, STRLEN, file_r)) != NULL) {
        flag = 1;
        len = strlen(line);

        if(line[len-1] == '\n')
            line[--len] = '\0';

        tmp = len - 1;

        // Check if it is palindrom
        for(int i=0; i < len/2 && flag; i++) {
            if(line[i] != line[tmp--])
                flag = 0;
        }

        if(flag) {
            strcat(line, "\n");
            fputs(line, file_w);
        }

    }

    fclose(file_r);
    fclose(file_w);
    free(line);
}

void write_palims(int fd) {
    int retcode;
    FILE* file;
    char* line;

    // Open stream from fd
    file = fdopen(fd, "read");
    check_ptr_err(file, "fdopen write pal");

    line = malloc(STRLEN);
    while((line = fgets(line, STRLEN, file)) != NULL) {
        printf("\033[34;1mpalindrome: %s", line);
    }
}

int main(int argc, char **argv)
{
    int retcode;
    int pipe_r[2];
    int pipe_w[2];
    char buffer[STRLEN];

    if (argc > 2)
    {
        printf("\033[31;1mUSE: %s <input-file>\033[0m\n");
        exit(1);
    }

    // Create pipe to communicate with R
    retcode = pipe(pipe_r);
    check_err(retcode, "pipe");

    // Create pipe to communicate wit W
    retcode = pipe(pipe_w);
    check_err(retcode, "pipe w");

    if (fork() != 0)
    {
        if (fork() != 0)
        {
            // Close unused channels
            close(pipe_w[0]);
            close(pipe_r[1]);
            
            // Wait for R to read file into pipe_r and check
            wait(NULL);
            check_palindrome(pipe_r, pipe_w);
            close(pipe_r[0]);
            close(pipe_w[1]);

            wait(NULL);
        }
        else
        {
            // Close unused channels
            close(pipe_r[0]);
            close(pipe_r[1]);
            close(pipe_w[1]);

            write_palims(pipe_w[0]);
        }
    }
    else
    {
        if (argc > 1)
            read_file(pipe_r, argv[1]);
        else
            read_file(pipe_r, NULL);
    }
}