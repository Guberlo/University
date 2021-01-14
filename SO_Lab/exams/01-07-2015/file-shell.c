/**
 * https://diraimondo.dmi.unict.it/wp-content/uploads/classes/so/lab-exams/?get=compito_2015-07-01.pdf
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/dir.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLEN 1024
#define TYPE_PARENT 21412

typedef enum {
    CMD_LIST,
    CMD_SIZE,
    CMD_SEARCH,
    CMD_EXIT,
    RESP_LIST,
    RESP_SIZE,
    RESP_STOP,
    RESP_SEARCH,
    RESP_ERR
} payload;

typedef struct {
    long mid;
    char mtext[MAXLEN];
    payload mpload;
    long size;
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

const char* get_payload(payload pload ) {
    switch (pload) {
        case CMD_LIST: return "CMD_LIST";
        case CMD_SIZE: return "CMD_SIZE";
        case CMD_SEARCH: return "CMD_SEARCH";
        case CMD_EXIT: return "CMD_EXIT";
        case RESP_LIST: return "RESP_LIST";
        case RESP_STOP: return "RESP_STOP";
        default: return "NOT KNOWN";
    }
}

void execute_command(char* dirname, int num, int queue_fd) {
    msg mex;
    DIR* dir;
    FILE* file;
    struct stat sb;
    struct dirent* dirinfo;
    int retcode, done = 0;
    int search_occur;
    char buffer[MAXLEN];

    printf("\033[35;1mChild D-%d on directory %s\033[0m\n", num, dirname);

    // Change working dir
    retcode = chdir(dirname);
    check_err(retcode, "chdir");

    while(!done) {
        retcode = msgrcv(queue_fd, &mex, sizeof(mex), num, 0);
        check_err(retcode, "msgrcv");

        switch (mex.mpload) {
            case CMD_LIST:
                dir = opendir(".");
                check_ptr_err(dir, "opendir");
                printf("\033[35;1mPAYLOAD: CMD_LIST\033[0m\n");

                // Read files and send a message containing file name
                while((dirinfo = readdir(dir)) != NULL) {
                    retcode = lstat(dirinfo->d_name, &sb);
                    check_err(retcode, "lstat");
                    // Check if it is a regular file
                    if(S_ISREG(sb.st_mode)) {
                        mex.mid = TYPE_PARENT; // Used to receive info on father
                        mex.mpload = RESP_LIST;
                        strncpy(mex.mtext, dirinfo->d_name, MAXLEN);

                        retcode = msgsnd(queue_fd, &mex, sizeof(mex), 0);
                        check_err(retcode, "msgsnd LIST");
                    }
                }
                // After we finish we need to send an end message
                mex.mid = TYPE_PARENT;
                mex.mpload = RESP_STOP;
                retcode = msgsnd(queue_fd, &mex, sizeof(mex), 0);
                check_err(retcode, "msgsnd");

                closedir(dir);
                break;
            case CMD_SIZE:
                dir = opendir(".");
                check_ptr_err(dir, "opendir size");
                printf("\033[35;1mPAYLOAD: CMD_SIZE\033[0m\n");

                // Scan files to see if file is present in directory
                while((dirinfo = readdir(dir)) != NULL) {
                    if(strcmp(mex.mtext, dirinfo->d_name) != 0)
                        continue;
                    // Get file stat to check dimension
                    retcode = lstat(mex.mtext, &sb);
                    check_err(retcode, "lstat size");

                    // Init message attributes
                    mex.mid = TYPE_PARENT;
                    mex.mpload = RESP_SIZE;
                    mex.size = sb.st_size;

                    retcode = msgsnd(queue_fd, &mex, sizeof(mex), 0);
                    check_err(retcode, "msgsnd SIZE");

                    closedir(dir);
                    break;
                }
                mex.mid = TYPE_PARENT;
                mex.mpload = RESP_STOP;

                retcode = msgsnd(queue_fd, &mex, sizeof(mex), 0);
                check_err(retcode, "msgsnd SIZE");
                break;
            case CMD_SEARCH:
                printf("\033[35;1mPAYLOAD: CMD_SEARCH\033[0m\n");
                // Check if file is regular
                if(lstat(mex.mtext, &sb) == -1 || !S_ISREG(sb.st_mode) || (file = fopen(mex.mtext, "r")) == NULL) {
                    mex.mid = TYPE_PARENT;
                    mex.mpload = RESP_ERR;
                    retcode = msgsnd(queue_fd, &mex, sizeof(mex), 0);
                    check_err(retcode, "msgsnd search err");

                    // Extract the second message to clean queue
                    msgrcv(queue_fd, &mex, sizeof(mex), num, 0);

                    break;
                }
                
                // Get second message containing string to search
                retcode = msgrcv(queue_fd, &mex, sizeof(mex), num, 0);
                check_err(retcode, "msgrcv search second");
                
                search_occur = 0;
                while(fgets(buffer, MAXLEN, file) != NULL) {
                    if(strstr(buffer, mex.mtext) != NULL)
                        search_occur++;
                }

                fclose(file);
                // Send the message containing no. of occurrences of string
                mex.mid = TYPE_PARENT;
                mex.mpload = RESP_SEARCH;
                mex.size = search_occur;

                retcode = msgsnd(queue_fd, &mex, sizeof(mex), 0);
                check_err(retcode, "msgsnd SEARCH");

                break;
            case CMD_EXIT:
                printf("\033[35;1mPAYLOAD: CMD_EXIT\033[0m\n");
                done = 1;
                break;            
            default:
                printf("\033[31;1mWTF IS THAT PAYLOAD??\033[0m\n");
                break;
        }
    }
    printf("\033[31;1mChild D-%d exit\033[0m\n", num);

}

int main(int argc, char** argv) {
    int queue_fd;
    int retcode, done = 0;
    int len, dirno, children;
    char* command, *filename, *tosearch = NULL;
    struct stat sb;
    char buffer[MAXLEN];
    msg mex;
    payload request;

    if(argc < 2) {
        printf("\033[31;1mUSE: %s <directory-1> <directory-2> <...>\033[0m\n", argv[0]);
        exit(1);
    }

    // Create queue
    queue_fd = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0660);
    check_err(queue_fd, "msgget");

    // Create as many children as num of arguments
    children = 0;
    for(int i=1; i<argc; i++) {
        if(lstat(argv[i], &sb) == 1 || !S_ISDIR(sb.st_mode)) {
            printf("\033[31;1mERROR: it seems that %s is not a directory...\033[0m\n");
            continue;
        }
        children++;
        if(fork() == 0) {
            execute_command(argv[i], i, queue_fd);
            exit(0);
        }
    }

    // Interactive shell
    do {
        printf("\033[34;1m$ \033[0m");
        fgets(buffer, MAXLEN, stdin);
        len = strlen(buffer);

        if(buffer[len - 1] == '\n')
            buffer[--len] = '\0';
        
        // Get command and dirno
        command = strtok(buffer, " ");
        printf("\033[34;1mCOMMAND: '%s'\033[0m\n", command);

        if(strncmp(command, "exit", len) == 0 || strncmp(command, "quit", len) == 0) {
            printf("\033[31;1mWTFAPPENZ\033[0m\n");
            done = 1;
            break;
        }

        if(strcmp(command, "list") != 0 && strncmp(command, "size", len) != 0 && strncmp(command, "search", len) != 0) {
            printf("\033[31;1mUSE: list n || size n filename || search n filename tosearch\033[0m\n");
            continue;
        }


        dirno = atoi(strtok(NULL, " "));
        printf("\033[31;1mDIRNO: %d\033[0m\n", dirno);

        // Validate dirno
        if(dirno > 0 && dirno <= children) {
            mex.mid = dirno;
            if(strcmp(command, "list") == 0) {
                printf("\033[33;1mFATHER: COMMAND RECEIVED LIST\033[0m\n");
                mex.mpload = CMD_LIST;

                retcode = msgsnd(queue_fd, &mex, sizeof(mex), 0);
                check_err(retcode, "msgsnd list");

                while(1) {
                    retcode = msgrcv(queue_fd, &mex, sizeof(mex), TYPE_PARENT, 0);
                    check_err(retcode, "msgrcv father list");

                    // Check if we have read all files using payload
                    if(mex.mpload == RESP_STOP) 
                        break;
                    
                    printf("\033[34;1m%s\033[0m\n", mex.mtext);
                }
            }
            else if(strcmp(command, "size") == 0) {
                mex.mpload = CMD_SIZE;
                filename = strtok(NULL, " ");
                strcpy(mex.mtext, filename);

                retcode = msgsnd(queue_fd, &mex, sizeof(mex), 0);
                check_err(retcode, "msgsnd size");

                while (1) {
                    retcode = msgrcv(queue_fd, &mex, sizeof(mex), TYPE_PARENT, 0);
                    check_err(retcode, "msgrcv SIZE");

                    if(mex.mpload == RESP_STOP)
                        break;

                    printf("\033[35;1m%s size: %ld B\033[0m\n", filename, mex.size);
                }
            }
            else if(strcmp(command, "search") == 0) {
                // Due to the dimension limitation we need to send two different messages
                // First one: contains filename
                mex.mpload = CMD_SEARCH;
                filename = strtok(NULL, " ");
                strcpy(mex.mtext, filename);

                retcode = msgsnd(queue_fd, &mex, sizeof(mex), 0);
                check_err(retcode, "msgsnd search 1");

                // Second one: string to search
                tosearch = strtok(NULL, " ");
                strncpy(mex.mtext, tosearch, sizeof(tosearch));
                retcode = msgsnd(queue_fd, &mex, sizeof(mex), 0);
                check_err(retcode, "msgsnd search 2");

                // Receive response
                retcode = msgrcv(queue_fd, &mex, sizeof(mex), TYPE_PARENT, 0);
                check_err(retcode, "msgrcv search");

                if(mex.mpload == RESP_ERR)
                    printf("\033[31;1mFATHER: error from child!\033[0m\n");
                else
                    printf("\033[35;1mFOUND %ld number of occurrences!\033[0m\n", mex.size);
            }
        } 
        else {
            printf("\033[31;1mUSE a valid dir number!\033[0m\n");
            continue;
        }

    } while(!done);

    for(int i=1; i<=children; i++) {
        mex.mid = i;
        mex.mpload = CMD_EXIT;
        retcode = msgsnd(queue_fd, &mex, sizeof(mex), 0);
        check_err(retcode, "msgsnd exit");
    }

    for(int i=1; i<=children; i++)
        wait(NULL);
    
    
    retcode = msgctl(queue_fd, IPC_RMID, NULL);
    check_err(retcode, "msgctl");
}