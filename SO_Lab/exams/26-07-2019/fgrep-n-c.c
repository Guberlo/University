/**
 * 18.44
 * https://diraimondo.dmi.unict.it/wp-content/uploads/classes/so/lab-exams/?get=compito_2019-07-26.pdf
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define STRLEN 1024
#define RESP_RECEIVER 897
#define STOP "!!!-STOP_!!!"

typedef struct {
    long mtype;
    char word[STRLEN];
}  request;

typedef struct {
    long mtype;
    char line[STRLEN];
    char filename[STRLEN];
    char word[STRLEN];
    int row;
    int f_id;
} response;

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

void process_file(int request_queue, int response_queue, char* filename, int index) {
    int retcode, fd, row;
    char* data_ptr;
    char* token, *line;
    struct stat sb;
    request req_msg;
    response resp_msg;

    if(lstat(filename, &sb) == -1 || !S_ISREG(sb.st_mode) || (fd = open(filename, O_RDONLY)) == -1) {
        printf("\033[31;1mERROR: file %s not supported\033[0m\n", filename);
        perror(filename);
        exit(1);
        // SIGNAL OTHERS?
    }

    // Map file into mm
    data_ptr = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    check_ptr_err(data_ptr, "mmap");

    char tmp_file[sb.st_size];


    close(fd);

    // SET A CONDITION TO STOP (request == "!!!STOPREQ!!!")
    token = malloc(STRLEN);
    resp_msg.mtype = RESP_RECEIVER;
    while(1) {
        strncpy(tmp_file, data_ptr, sb.st_size);
        retcode = msgrcv(request_queue, &req_msg, sizeof(req_msg), index, 0);
        check_err(retcode, "msgrcv");

        if(strcmp(req_msg.word, STOP) == 0) {
            strncpy(resp_msg.line, STOP, STRLEN);
            retcode = msgsnd(response_queue, &resp_msg, sizeof(resp_msg), 0);
            check_err(retcode, "msgsnd stop");
            break;
        }

        // NOTE: THERE IS A PROBLEM. THE NUMBER OF LINES WON'T BE CORRECT SINCE WE REMOVE \n
        token = strtok(tmp_file, "\n");
        row = 1;
        do {
            if(strstr(token, req_msg.word)) {
                // SEND A MESSAGE 
                resp_msg.row = row;
                resp_msg.f_id = index;
                strncpy(resp_msg.word, req_msg.word, STRLEN);
                strncpy(resp_msg.line, token, STRLEN);
                strncpy(resp_msg.filename, filename, STRLEN);
                retcode = msgsnd(response_queue, &resp_msg, sizeof(resp_msg), 0);
                check_err(retcode, "msgsnd fgrep");
            }
            row++;
        } while((token = strtok(NULL, "\n")) != NULL);

    }

    exit(0);
}

void send_request(int request_queue, char* word, int children) {
    int retcode;
    request request_msg;


    strncpy(request_msg.word, word, STRLEN);
    for(int i=0; i<children; i++) {
        request_msg.mtype = i+1;
        retcode = msgsnd(request_queue, &request_msg, sizeof(request_msg), 0);
        check_err(retcode, "msgsnd request");
    }
}

void recv_response(int response_queue, int children) {
    int retcode, completed = 0;
    int occurences[children];
    response response_msg;

    for(int i=0; i<children; i++)
        occurences[i] = 0;
    
    while(1) {
        retcode = msgrcv(response_queue, &response_msg, sizeof(response_msg), RESP_RECEIVER, 0);
        check_err(retcode, "msgrcv response");

        if(strcmp(response_msg.line, STOP) == 0) {
            completed++;
            if(completed == children)
                break;
            continue;
        }
        
        printf("\033[36;1m%s@%s:%d:%s\033[0m\n", response_msg.word, response_msg.filename, response_msg.row, response_msg.line);
        occurences[response_msg.f_id-1]++;
    }

    for(int i=0; i<children; i++)
        printf("\033[33;1mFILE%d:%d\033[0m\n", i+1, occurences[i]);
}

int main(int argc, char** argv) {
    int request_queue, response_queue, retcode;
    request request_msg;

    if(argc < 4) {
        printf("\033[31;1mUSE: %s <word-1> [word-2] .... @ <file-1> [file-2] ....\n", argv[0]);
        exit(1);
    }

    // Create msg queue
    request_queue = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0660);
    check_err(request_queue, "msgget");

    response_queue = msgget(IPC_PRIVATE+1, IPC_CREAT | IPC_EXCL | 0660);
    check_err(response_queue, "msgget");

    int index=0;
    while(strcmp(argv[index], "@") != 0)
        index++;
    
    // Take from argv[1] to argv[index-1]
    char** words = argv + 1;
    int words_count  = index - 1;

    // Take from argv[index+1] to argv[argc-index-1] 
    char** files = argv + index + 1;
    int files_count = argc - index - 1;

    for(int i=0; i<files_count; i++)
        if(fork() == 0)
            process_file(request_queue, response_queue, files[i], i+1);

    for(int i=0; i<words_count; i++) {
        // Send a request to each child
        send_request(request_queue, words[i], files_count);
    }

    strncpy(request_msg.word, STOP, STRLEN);
    for(int i=0; i<files_count; i++) {
        request_msg.mtype = i+1;

        retcode = msgsnd(request_queue, &request_msg, sizeof(request_msg), 0);
        check_err(retcode, "msgsnd eof");
    }

    recv_response(response_queue, files_count);

    // Deallocate
    retcode = msgctl(request_queue, IPC_RMID, NULL);
    check_err(retcode, "msgctl");

    retcode = msgctl(response_queue, IPC_RMID, NULL);
    check_err(retcode, "msgctl");
}