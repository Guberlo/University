/**
 * https://diraimondo.dmi.unict.it/wp-content/uploads/classes/so/lab-exams/?get=compito_2018-12-18.pdf
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define STRLEN 1024

typedef struct {
    long mtype;
    char line[STRLEN];
    char eof;
} message;

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

void reader(int* p_fd, char* filename) {
    int retcode, len;
    char* line;
    struct stat sb;
    FILE* file_in, *file_out;

    // Close input channel on pipe
    close(p_fd[0]);
    
    if(lstat(filename, &sb) == -1 || !S_ISREG(sb.st_mode) || (file_in = fopen(filename, "r")) == NULL) {
        printf("\033[31;1mERROR: file %s not supported\033[0m\n", filename);
        exit(1);
    }

    // Open pipe output as stream
    file_out = fdopen(p_fd[1], "w");
    check_ptr_err(file_out, "fdopen");

    line = malloc(STRLEN);
    while(fgets(line, STRLEN, file_in)) {
        fputs(line, file_out);
    }

    fclose(file_in);
    fclose(file_out);
    close(p_fd[1]);
    exit(0);
}

void writer(int queue, int* p_fd) {
    int retcode;
    message msg;

    close(p_fd[0]);
    close(p_fd[1]);

    while(1) {
        retcode = msgrcv(queue, &msg, sizeof(message)- sizeof(long), 0, 0);
        check_err(retcode, "msgrcv");

        if(msg.eof == 1)
            break;
        
        printf("\033[33;1m%s\033[0m\n", msg.line);
    }

    exit(0);
}

void grep(int* p_fd, int queue, char* word) {
    int retcode, len;
    char* line;
    FILE* file;
    message msg;

    // Close output channel on pipe
    close(p_fd[1]);

    // Open input pipe as stream
    file = fdopen(p_fd[0], "r");
    check_ptr_err(file, "fdopen");

    msg.mtype = 1;
    msg.eof = 0;
    line = malloc(STRLEN);
    while(fgets(line, STRLEN, file)) {
        len = strlen(line);

        if(line[len-1] == '\n')
            line[--len] = '\0';
        
        if(strstr(line, word)) {
            strncpy(msg.line, line, STRLEN);

            retcode = msgsnd(queue, &msg, sizeof(message) - sizeof(long), 0);
            check_err(retcode, "msgsdn");
        }
    }

    // Send eof
    msg.eof = 1;
    retcode = msgsnd(queue, &msg, sizeof(message)- sizeof(long), 0);
    check_err(retcode, "msgsnd eof");

    fclose(file);
    close(p_fd[0]);
}

int main(int argc, char** argv) {
    int retcode, queue;
    int p_fd[2];

    if(argc != 3) {
        printf("\033[31;1mUSE: %s <parola> <file>\033[0m\n", argv[0]);
        exit(1);
    }

    // Create pipe
    retcode = pipe(p_fd);
    check_err(retcode, "pipe");

    // Create msg queue
    queue = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0660);
    check_err(queue, "msgget");

    if(fork() != 0) {
        if(fork() != 0) {
            wait(NULL);
            grep(p_fd, queue, argv[1]);
            wait(NULL);

            // Deallocate
            retcode = msgctl(queue, IPC_RMID, NULL);
            check_err(retcode, "msgctl");
        }
        else 
            writer(queue, p_fd);
    }
    else
        reader(p_fd, argv[2]);
}