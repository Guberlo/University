/**
 * https://diraimondo.dmi.unict.it/wp-content/uploads/classes/so/lab-exams/?get=compito_2015-10-08.pdf
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

#define STRLEN 1024

typedef struct {
    long mtype;
    char mtext[STRLEN];
} msg;

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
    struct stat statbuf;
    int retcode;
    char* line;
    FILE* p_file, *src_file;

    printf("\033[35;1mR started\033[0m\n");
    close(pipe_fd[0]);

    p_file = fdopen(pipe_fd[1], "w");
    check_ptr_err(p_file, "fdopen");

    // Check if it is a valid file
    if(lstat(filename, &statbuf) == -1 || !S_ISREG(statbuf.st_mode)) {
        perror("file");
        printf("\033[31;1mNOT A REGULAR FILE\033[0m\n");
        retcode = fputs("ERROR\n", p_file);
        check_err(retcode, "fputs");

        fclose(p_file);
        close(pipe_fd[1]);
        exit(1);
    }

    // Read each line of file and write to pipe output
    src_file = fopen(filename, "r");
    check_ptr_err(src_file, "fopen src");

    line = malloc(STRLEN);
    while((line = fgets(line, STRLEN, src_file)) != NULL) {
        retcode = fputs(line, p_file);
        check_err(retcode, "fputs output");
    }

    free(line);

    printf("\033[35;1mR: finished writing file to pipe.\033[0m\n");
    fclose(p_file);
    fclose(src_file);
    close(pipe_fd[1]);
    exit(0);
}

void print_grep(int queue) {
    msg mex;
    int retcode;

    mex.mtype = -1;

    while(mex.mtype != 2) {
        retcode = msgrcv(queue, &mex, sizeof(mex), 0, 0);
        check_err(retcode, "msgrcv");
        if(mex.mtype == 2)
            break;
        
        printf("\033[36;1m%s\033[0m\n", mex.mtext);
    }
    
    exit(0);
}

void send_data(int queue, int fd, char* tosearch) {
    char* line;
    int retcode;
    msg mex;
    FILE* file;

    // Get stream from fd
    file = fdopen(fd, "r");
    check_ptr_err(file, "fdopen snd data");

    // Read line-by-line from file stream
    line = malloc(STRLEN);
    mex.mtype = 1;
    while((line = fgets(line, STRLEN, file)) != NULL) {
        // Send each line if it contains the string
        if(strstr(line, tosearch) != NULL) {
            strncpy(mex.mtext, line, STRLEN);

            retcode = msgsnd(queue, &mex, sizeof(mex), 0);
            check_err(retcode, "msgsnd snd data");
        }
    }
    // Send EOF
    mex.mtype = 2;
    strncpy(mex.mtext, "!EOF!\n", STRLEN);

    retcode = msgsnd(queue, &mex, sizeof(mex), 0);
    check_err(retcode, "msgsnd EOF");

    free(line);
    fclose(file);
    close(fd);
}

int main(int argc, char** argv) {
    int pipe_fd[2];
    int queue, retcode;

    if(argc != 3) {
        printf("\033[31;1mUSE: %s <tosearch> <filename>\033[0m\n");
        exit(1);
    }

    // Create queue
    queue = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0660);
    check_err(queue, "msgget");

    // Create pipe
    retcode = pipe(pipe_fd);
    check_err(retcode, "pipe");

    if(fork() != 0) {
        if(fork() != 0) {
            close(pipe_fd[1]);
            wait(NULL);
            // Send received data to W
            send_data(queue, pipe_fd[0], argv[1]);
            wait(NULL);

            // Deallocate queue
            retcode = msgctl(queue, IPC_RMID, NULL);
            check_err(retcode, "msgctl rm");
        }
        else {
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            print_grep(queue);
        }
    }
    else 
        read_file(pipe_fd, argv[2]);
    
}
