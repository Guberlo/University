/**
 * https://diraimondo.dmi.unict.it/wp-content/uploads/classes/so/lab-exams/?get=compito_2020-09-25.pdf
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

#define STRLEN 32
#define MAX_ROWS 100

typedef struct {
    long mtype;
    char mtext[STRLEN];
    char eof;
} msg;

void check_err(int val, char* msg) {
    if(val == -1) {
        perror(msg);
        exit(1);
    }
}

void reader(int queue, char* filename) {
    int len, retcode;
    char* line;
    struct stat sb;
    msg mex;
    FILE* file;

    if(lstat(filename, &sb) == -1 || !S_ISREG(sb.st_mode) || (file = fopen(filename, "r")) == NULL) {
        printf("\033[31;1mERROR: file not supported. . .\033[0m\n");
        mex.eof = 1;
        strcpy(mex.mtext, "EOF REACHED!!");

        retcode = msgsnd(queue, &mex, sizeof(mex), 0);
        check_err(retcode, "msgsnd");
    }

    line = malloc(STRLEN);
    mex.eof = 0;
    while(fgets(line, STRLEN, file)) {
        len = strlen(line);

        if(line[len-1] == '\n')
            line[--len] = '\0';

        int j = 0;
        memset(mex.mtext, 0, STRLEN);
        for(int i=0; i<len; i++) {
            // Remove spaces from beginning and end
            if((i == 0 || i == len-1) && line[i] == ' ')
                continue;
            if(line[i] == '\n')
                continue;
            
            mex.mtext[j++] = line[i];
        }

        retcode = msgsnd(queue, &mex, sizeof(mex), 0);
        check_err(retcode, "msgsnd");
    }

    // Send EOF
    mex.eof = 1;
    strcpy(mex.mtext, "EOF REACHED!!");

    retcode = msgsnd(queue, &mex, sizeof(mex), 0);
    check_err(retcode, "msgsnd");

    free(line);
    fclose(file);
    exit(0);
}

void check_and_send(int queue, int* p_fd) {
    int retcode, eof_count = 0;
    char words[MAX_ROWS*2][STRLEN] = {""};
    char found;
    FILE* file;
    msg mex;


    // Open output stream
    file = fdopen(p_fd[1], "w");

    int elems = 0;
    mex.eof = 0;
    while(eof_count != 2) {
        retcode = msgrcv(queue, &mex, sizeof(mex), 0, 0);
        check_err(retcode, "msgrcv");

        if(mex.eof == 1)
            eof_count++;
        else {
            found = 0;
            for(int i=0; i<MAX_ROWS*2; i++) {
                printf("\033[31;1m%s == %s\033[0m\n", mex.mtext, words[i]);
                if(strcasecmp(mex.mtext, words[i]) == 0)
                    found = 1;
            }

            if(found == 0) {
                strncpy(words[elems++], mex.mtext, STRLEN);
                strcat(mex.mtext, "\n");
                fputs(mex.mtext, file);
            }
        }
    }

    fclose(file);
}

void writer(int* p_fd) {
    FILE* file;
    char* line;
    printf("\033[31;1mWRITER STARTED\033[0m\n");
    close(p_fd[1]);

    // Open input stream
    file = fdopen(p_fd[0], "r");

    line = malloc(STRLEN);
    while(fgets(line, STRLEN, file))
        printf("\033[34;1m%s\033", line);

    close(p_fd[0]);
}

int main(int argc, char** argv) {
    int queue, retcode;
    int p_fd[2];

    if(argc != 3) {
        printf("\033[31;1mUSE: %s  <file-1> <file-2>\033[0m\n", argv[0]);
        exit(1);
    }

    // Create message queue
    queue = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0660);
    check_err(queue, "msgget");

    // Create pipe
    retcode = pipe(p_fd);
    check_err(retcode, "pipe");

    if(fork() != 0) {
        if(fork() != 0) {
            check_and_send(queue, p_fd);
            if(fork() != 0) {
                wait(NULL);
                wait(NULL);
                wait(NULL);

                close(p_fd[0]);
                close(p_fd[1]);

                retcode = msgctl(queue, IPC_RMID, NULL);
                check_err(retcode, "msgctl");
            }
            else {
                writer(p_fd);
            }
        }
        else {
            close(p_fd[0]);
            close(p_fd[1]);
            reader(queue, argv[2]);
        }
    }
    else {
        close(p_fd[0]);
        close(p_fd[1]);
        reader(queue, argv[1]);
    }
}