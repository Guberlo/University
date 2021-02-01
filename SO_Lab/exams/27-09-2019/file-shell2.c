/**
 * https://diraimondo.dmi.unict.it/wp-content/uploads/classes/so/lab-exams/?get=compito_2019-09-27.pdf
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define MAX_LEN 1024

typedef struct {
    long mtype;
    char command;
    char filename[MAX_LEN];
    char c_to_search;
    char eof;
} message;

void check_err(int val, char* msg) {
    if(val == -1) {
        perror(msg);
        exit(1);
    }
}

void terminal(int queue, int argc) {
    int len, retcode, dirno;
    char* command, *filename, *to_search, *token;
    message msg;
    msg.eof = 0;

    command = malloc(MAX_LEN);
    filename = malloc(MAX_LEN);
    token = malloc(MAX_LEN);
    to_search = malloc(sizeof(char));

    while(1) {
        printf("\033[34;1m$ \033[0m");
        fgets(command, MAX_LEN, stdin);
        len = strlen(command);

        if(command[len-1] == '\n')
            command[--len] = '\0';
        
        strcpy(token, command);
        strtok(token, " ");
        
        printf("token: %s\n", token);

        if(strcmp(token, "quit") == 0 || strcmp(token, "exit") == 0)
            break;
        
        if(strcmp(token, "num-files") == 0) {
            strtok(command, " ");
            dirno = atoi(strtok(NULL, " "));

            if(dirno > argc || dirno < argc || dirno == 0) {
                printf("\033[31;1mERROR: dirno not in range\033[0m\n");
                continue;
            }

            // Send msg
            msg.command = 'N';
            msg.mtype = dirno;

            retcode = msgsnd(queue, &msg, sizeof(message), 0);
            check_err(retcode, "msgsnd");

            printf("\033[31;1mSENT: command: %c\ttype:%ld\033[0m\n", msg.command, msg.mtype);

        }
        else if(strcmp(token, "total-size") == 0) {
            strtok(command, " ");
            dirno = atoi(strtok(NULL, " "));

            if(dirno > argc || dirno < argc || dirno == 0) {
                printf("\033[31;1mERROR: dirno not in range\033[0m\n");
                continue;
            }

            msg.command = 'T';
            msg.mtype = dirno;

            retcode = msgsnd(queue, &msg, sizeof(message), 0);
            check_err(retcode, "msgsnd");

            printf("\033[31;1mSENT: command: %c\ttype:%ld\033[0m\n", msg.command, msg.mtype);
        }
        else if(strcmp(token, "search-char") == 0) {
            strtok(command, " ");
            dirno = atoi(strtok(NULL, " "));
            strncpy(filename, strtok(NULL, " "), MAX_LEN);
            strncpy(to_search, strtok(NULL, " "), MAX_LEN);

            if(dirno > argc || dirno < argc || dirno == 0) {
                printf("\033[31;1mERROR: dirno not in range\033[0m\n");
                continue;
            }

            msg.command = 'S';
            msg.mtype = dirno;
            msg.c_to_search = to_search[0];
            strncpy(msg.filename, filename, MAX_LEN);

            retcode = msgsnd(queue, &msg, sizeof(message), 0);
            check_err(retcode, "msgsnd");

            printf("\033[31;1mSENT: command: %c\ttype:%ld\tfilename: %s c_to_s: %c\033[0m\n", msg.command, msg.mtype, msg.filename, msg.c_to_search);
        }
        else {
            printf("\033[31;1mERROR: unknown command.\033[0m\n");
            continue;
        }
    }

    free(command);
    free(filename);
    free(token);
    free(to_search);
}

void dir_stat(int queue, char* dirname, int dirno) {
    int retcode, len, fd, result = 0;
    struct stat sb;
    struct dirent* dir_info;
    char* data_ptr;
    DIR* dir;
    message msg;
    msg.eof = 0;
    char debug[MAX_LEN];

    if(lstat(dirname, &sb) == -1 || !S_ISDIR(sb.st_mode) || (dir = opendir(dirname)) == NULL) {
        printf("\033[31;1mERROR: file not supported\033[0m\n");
        exit(1);
    }

    chdir(dirname);

    while(msg.eof != 1) {
        result = 0;
        retcode = msgrcv(queue, &msg, sizeof(msg), dirno, 0);
        check_err(retcode, "msgrcv");

        if(msg.eof == 1)
            break;

        if(msg.command == 'N') {
            while((dir_info = readdir(dir)) != NULL) {
                retcode = lstat(dir_info->d_name, &sb);
                check_err(retcode, "lstat");

                if(S_ISREG(sb.st_mode))
                    result++;
            }
            printf("\033[33;1m%d regular files\033[0m\n", result);
        }
        else if(msg.command == 'T') {
            while((dir_info = readdir(dir)) != NULL) {
                retcode = lstat(dir_info->d_name, &sb);
                check_err(retcode, "lstat");

                if(S_ISREG(sb.st_mode)) {
                    result += sb.st_size;
                }
            }
            printf("\033[33;1m%dB\033[0m\n", result);
        }
        else if(msg.command == 'S') {
            if(lstat(msg.filename, &sb) == -1 || !S_ISREG(sb.st_mode) || (fd = open(msg.filename, O_RDONLY)) == -1) {
                printf("\033[31;1mERROR: file %s not supported\033[0m\n", msg.filename);
                perror("can't open");
                printf("%s\n", getcwd(debug, MAX_LEN));
                continue;
            }

            data_ptr = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
            close(fd);

            for(int i=0; i<sb.st_size; i++)
                if(data_ptr[i] == msg.c_to_search)
                    result++;

            printf("\033[33;1m%d occurences of %c\033[0m\n", result, msg.c_to_search);

            retcode = munmap(data_ptr, sb.st_size);
            check_err(retcode, "munmap");
        }
    }

    chdir("..");
    exit(0);
}

int main(int argc, char** argv) {
    int retcode, queue;
    message msg;

    if(argc < 2) {
        printf("\033[31;1mUSE: %s <directory-1> <directory-2> . . . \033[0m\n", argv[0]);
        exit(1);
    }

    // Create msg queue
    queue = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0660);
    check_err(queue, "msgget");

    for(int i=1; i<argc; i++) {
        if(fork() == 0)
            dir_stat(queue, argv[i], i);
    }

    terminal(queue, argc-1);

    // Send EOF
    for(int i=1; i<argc; i++) {
        msg.mtype = i;
        msg.eof = 1;

        retcode = msgsnd(queue, &msg, sizeof(msg), 0);
        check_err(retcode, "msgsnd eof");
    }
    
    for(int i=1; i<argc; i++)
        wait(NULL);

    // Deallocate
    retcode = msgctl(queue, IPC_RMID, NULL);
    check_err(retcode, "msgctl");
}