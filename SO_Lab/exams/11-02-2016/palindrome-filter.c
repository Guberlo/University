/**
 * https://diraimondo.dmi.unict.it/wp-content/uploads/classes/so/lab-exams/?get=compito_2016-02-12.pdf
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>

#define STRLEN 1024

typedef struct {
    long mtype;
    char mtext[STRLEN];
    int eof;
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

void read_file(int queue, char* filename) {
    int retcode, len;
    int allocated = 0;
    char* line;
    struct stat statbuf;
    FILE* file;
    msg mex;

    // Check if filename has been passed
    if(filename == NULL) {
        filename = malloc(STRLEN);
        allocated = 1;
        printf("\033[36;1mInput file: \033[0m");
        fgets(filename, STRLEN, stdin);

        len = strlen(filename);
        if(filename[len-1] == '\n')
            filename[--len] = '\0';
        printf("%s\n", filename);
    }

    // Check if it is a regular file
    if(lstat(filename, &statbuf) == -1 || !S_ISREG(statbuf.st_mode)) {
        mex.mtype = 1;
        mex.eof = 1;
        strncpy(mex.mtext, "ERROR: file not supported", STRLEN);

        retcode = msgsnd(queue, &mex, sizeof(mex), 0);
        check_err(retcode, "msgsnd error read");
        if(allocated)
            free(filename);
        exit(1);
    }

    // Open stream to read each line
    file = fopen(filename, "r");
    check_ptr_err(file, "fopen");

    // Read each line
    line = malloc(STRLEN);
    mex.mtype = 1;
    mex.eof = 0;
    while((line = fgets(line, STRLEN, file)) != NULL) {
        // Remove \n
        len = strlen(line);
        if(line[len-1] == '\n')
            line[--len] = '\0';

        // Send message to father
        strncpy(mex.mtext, line, STRLEN);
        retcode = msgsnd(queue, &mex, sizeof(mex), 0);
        check_err(retcode, "msgsnd read");
    }

    // Send EOF
    mex.eof = 1;
    strncpy(mex.mtext, "EOF", STRLEN);

    retcode = msgsnd(queue, &mex, sizeof(mex), 0);
    check_err(retcode, "msgsnd");


    free(line);
    fclose(file);
    exit(0);
}

void palindrome_check(int queue) {
    int retcode, flag;
    int len;
    msg mex;

    mex.eof = 0;
    while(mex.eof != 1) {
        retcode = msgrcv(queue, &mex, sizeof(mex), 1, 0);
        check_err(retcode, "msgrcv");

        if(mex.eof == 1)
            break;

        len = strlen(mex.mtext) - 1;
        int tmp = len;

        // Check if it is palindrome
        flag = 1;
        for(int i=0; i<len/2 && flag; i++) {
            if(mex.mtext[i] != mex.mtext[tmp--])
                flag = 0;
        }

        if(flag) {
            // Send a message containing only palindrome word
            printf("\033[36;1m%s is palindrome!\033[0m\n", mex.mtext);
            mex.mtype = 2;
            mex.eof = 0;
            strncpy(mex.mtext, mex.mtext, STRLEN);

            retcode = msgsnd(queue, &mex, sizeof(mex), 0);
            check_err(retcode, "msgsnd");
        }
    }

    // Send EOF
    mex.eof = 1;
    mex.mtype = 2;
    strncpy(mex.mtext, "EOF", STRLEN);

    retcode = msgsnd(queue, &mex, sizeof(mex), 0);
    check_err(retcode, "msgsnd eof palindrome");
}

void write_palindrome(int queue, char* filename) {
    int retcode;
    msg mex;
    struct stat statbuf;
    FILE* output;

    if(filename == NULL) {
        output = stdout;
    }
    else {
        // Open stream from file
        if(lstat(filename, &statbuf) == -1 || !S_ISREG(statbuf.st_mode) || (output = fopen(filename, "w")) == NULL) {
            // Signal error on terminal
            printf("\033[31;1mFile not supported!!\033[0m\n");
            exit(1);
        }
    }

    // Now we can start receiving messages and write to file
    mex.eof = 0;
    while(mex.eof != 1) {
        retcode = msgrcv(queue, &mex, sizeof(mex), 2, 0);
        check_err(retcode, "msgrcv write_palindrome");

        if(mex.eof == 1)
            break;
        
        // Write message to output
        strcat(mex.mtext, "\n");
        fputs(mex.mtext, output);
    }

    fclose(output);
}

int main(int argc, char** argv) {
    int queue, retcode;
    msg mex;

    if(argc > 4) {
        printf("\033[31;1mUSE: %s [input-file] [output-file]\033[0m\n");
        exit(1);
    }

    // Create message queue
    queue = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0660);
    check_err(queue, "msgget");

    if(fork() != 0) {
        if(fork() != 0) {
            palindrome_check(queue);
            wait(NULL);
            wait(NULL);

            // Deallocate queue
            retcode = msgctl(queue, IPC_RMID, NULL);
            check_err(retcode, "msgctl");
        }
        else {
            if(argc > 2)
                write_palindrome(queue, argv[2]);
            else
                write_palindrome(queue, NULL);
        }
    }
    else {
        if(argc > 1)
            read_file(queue, argv[1]);
        else
            read_file(queue, NULL);
    }
}