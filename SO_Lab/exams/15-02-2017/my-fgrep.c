/**
 * https://diraimondo.dmi.unict.it/wp-content/uploads/classes/so/lab-exams/?get=compito_2017-02-15.pdf
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

#define STRLEN 1024

typedef struct {
    char line[STRLEN];
    char filename[STRLEN];
    char eof;
} msg;


void check_err(int val, char* msg) {
    if(val == -1) {
        perror(msg);
        exit(1);
    }
}

void reader(int queue, char* filename) {
    printf("\033[35;1mREADER STARTED\033[0m\n");
    int retcode, len;
    char* line;
    struct stat sb;
    FILE* file;
    msg mex;

    if(lstat(filename, &sb) == -1 || !S_ISREG(sb.st_mode) || (file = fopen(filename, "r")) == NULL) {
        // Send error msg
        mex.eof = 1;
        strcpy(mex.line, "ERROR: file not supported");

        retcode = msgsnd(queue, &mex, sizeof(mex), 0);
        check_err(retcode, "msgsnd err");
        exit(1);
    }

    line = malloc(STRLEN);
    mex.eof = 0;

    while(fgets(line, STRLEN, file)) {
        len = strlen(line);
        if(line[len-1] == '\n')
            line[--len] = '\0';
        
        strcpy(mex.filename, filename);
        strcpy(mex.line, line);
        retcode = msgsnd(queue, &mex, sizeof(mex), 0);
        check_err(retcode, "msgsnd reader");

        printf("\033[35;1mR: sent %s\t%s\033[0m\n", mex.filename, mex.line);
    }

    // Send eof
    printf("\033[31;!mSENDING A FUCKING EOF\033[0m\n");
    mex.eof = 1;
    retcode = msgsnd(queue, &mex, sizeof(mex), 0);
    check_err(retcode, "msgsnd err");

    printf("\033[35;1mFINISH\033[0m\n");
    exit(0);
}

void filterer(int queue, int* pipe_fd, char* tosearch, char inverted, char case_insensitive, int filenum) {
    printf("\033[34;1mFILTERER STARTED\033[0m\n");
    int retcode, flag;
    int i=0;
    msg mex;
    FILE* file;
    mex.eof = 0;
    close(pipe_fd[0]);

    file = fdopen(pipe_fd[1], "w");
    printf("PORCO DIO FILENUM: %d\n", filenum);
    while(mex.eof != 1) {
        retcode = msgrcv(queue, &mex, sizeof(mex), 0, 0);
        check_err(retcode, "msgrcv");

        if(mex.eof == 1) {
            i++;
            printf("i == filenum\7%d == %d\n", i, filenum);
            if(i == filenum)
                break;
            else {
                mex.eof = 0;
                continue;
            }
        }

        if(case_insensitive)
            flag = (strcasestr(mex.line, tosearch) != NULL);
        else
            flag = (strstr(mex.line, tosearch) != NULL);

        if(!inverted && flag || inverted && !flag) {
            fputs(mex.line, file);
            printf("\033[33;1mline: %s\033[0m\n", mex.line);
        }

    }

    printf("\033[34;1mRIP CIAO PROPRIO\033[0m\n");
    close(pipe_fd[1]);
    exit(0);
}

int main(int argc, char** argv) {
    int pid, prev_pid = 0, queue, retcode, filenum;
    char inverted = 0, case_insensitive = 0;
    char* tosearch = NULL;
    char* filename = NULL;
    int p_fd[2];

    if(argc < 3) {
        printf("\033[31;1mUSE: %s [-v] [-i] <word> <file-1> [file-2] . . . .\033[0m\n", argv[0]);
        exit(1);
    }

    // Create queue
    queue = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0660);
    check_err(queue, "msgget");

    // Create pipe
    retcode = pipe(p_fd);
    check_err(retcode, "pipe");

    filenum = argc - 2; // Number of argument minus executable name and word
    printf("\033[31;1mfilenum: %d\033[0m\n", filenum);

    for(int i=1; i<argc; i++)
        if(strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "-i") == 0)
            filenum--;

    // Create filterer
    tosearch = argv[argc - filenum - 1];
    if(fork() == 0)
        filterer(queue, p_fd, tosearch, inverted, case_insensitive, filenum);

    close(p_fd[1]);

    for(int i=1; i<argc; i++) {
        if(!inverted && strcmp(argv[i], "-v") == 0)
            inverted = 1;
        else if(!case_insensitive && strcmp(argv[i], "-i") == 0)
            case_insensitive = 1;
        else if(strlen(argv[i]) > 0) {
            if(tosearch == NULL){
                tosearch = argv[i]; 
            }
            else {
                filename = argv[i];
                // Create reader
                if( (pid = fork()) == 0){
                    // Check if there is still a reader executing and wait for it to finish
                    reader(queue, filename);
                }
                else 
                    wait(NULL);
            }
        }
    }

    wait(NULL);

    // Read from pipe[0]

    close(p_fd[0]);

    printf("\033[31;1m queue destroyed\033[0m\n"),
    retcode = msgctl(queue, IPC_RMID, NULL);
    check_err(retcode, "msgctl");
}

