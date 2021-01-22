/**
 * https://diraimondo.dmi.unict.it/wp-content/uploads/classes/so/lab-exams/?get=compito_2016-10-07.pdf
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <libgen.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <sys/mman.h>

#define MAXLEN 2048

typedef struct {
    long type;
    char path[MAXLEN];
    int eof;
} msg;

typedef struct {
    long type;
    int total;
} msg_count;

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

void scanner(int queue, char* dir_path, int i) {
    DIR* dir;
    struct dirent* dir_info;
    struct stat sb;
    msg mex;
    char* filename;
    char file_path[MAXLEN];
    int retcode;

    dir = opendir(dir_path);
    check_ptr_err(dir, "opendir");

    retcode = chdir(dir_path);
    check_err(retcode, "chdir");

    mex.eof = 0;
    mex.type = 1;
    while((dir_info = readdir(dir))) {
        filename = dir_info->d_name;

        retcode = lstat(filename, &sb);
        check_err(retcode, "lstat");

        if(S_ISREG(sb.st_mode)) {
            getcwd(file_path, MAXLEN);
            strcat(file_path, "/");
            strcat(file_path, filename);
            printf("\033[34;1mScanner: %s \033[0m\n", file_path);

            strncpy(mex.path, file_path, MAXLEN);
            retcode = msgsnd(queue, &mex, sizeof(mex), 0);
            check_err(retcode, "msgsnd");
        }
        else if(S_ISDIR(sb.st_mode)) {
            if(strcmp(filename, ".") != 0 && strcmp(filename, "..") != 0){
                scanner(queue, filename, i + 1);
            }
        }
    }
    if(i == 0) {
        mex.eof = 1;
        mex.type = 1;
        strncpy(mex.path, "EOF", MAXLEN);

        retcode = msgsnd(queue, &mex, sizeof(mex), 0);
        check_err(retcode, "msgsnd EOF");

        exit(0);
    }

    chdir("..");
    closedir(dir);
}

int get_letters_count(char* filename) {
    char* data_ptr;
    char* dir_path;
    int fd, retcode;
    int total = 0;
    struct stat sb;

    retcode = stat(filename, &sb);
    check_err(retcode, filename);

    if(sb.st_size > 0) {
        fd = open(filename, O_RDONLY);
        check_err(fd, "open");

        data_ptr = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
        check_ptr_err(data_ptr, "mmap");

        close(fd);

        for(int i=0; i<sb.st_size; i++) {
            if((data_ptr[i] >= 'A' && data_ptr[i] <= 'Z') || (data_ptr[i] >= 'a' && data_ptr[i] <= 'z') ){
                total++;
            }
        }

        retcode = munmap(data_ptr, sb.st_size);
        check_err(retcode, filename);
    }

    return total;
}

void analyzer(int queue) {
    int total, retcode;
    msg mex;
    msg_count mex_count;

    mex.eof = 0;
    mex_count.type = 2;
    while(mex.eof != 1) {
        retcode = msgrcv(queue, &mex, sizeof(mex), 1, 0);
        check_err(retcode, "msgrcv");

        if(mex.eof == 1)
            break;
        
        total = get_letters_count(mex.path);
        printf("\033[33;1mAnalyzer: %s <%d>\033[0m\n", mex.path, total);

        mex_count.total = total;
        retcode = msgsnd(queue, &mex_count, sizeof(mex_count), 0);
        check_err(retcode, "msgsnd");
    }

    mex_count.total = -1;
    retcode = msgsnd(queue, &mex_count, sizeof(mex_count), 0);
    check_err(retcode, "msgsnd");

    exit(0);
}

void sum_totals(int queue) {
    msg_count mex_count;
    int retcode;
    long int overall = 0;

    mex_count.total = 0;
    while(mex_count.total != -1) {
        retcode = msgrcv(queue, &mex_count, sizeof(mex_count), 2, 0);
        check_err(retcode, "msgrcv");
        
        if(mex_count.total == -1)
            break;

        overall += mex_count.total;
    }

    printf("\033[35;1mFather: %ld total characters.\033[0m\n", overall);
}

int main(int argc, char** argv) {
    int queue, retcode;

    if(argc > 2) {
        printf("\033[31;1mUSE: %s [directory]\033[0m\n", argv[0]);
        exit(1);
    }

    // Create message queue
    queue = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0660);
    check_err(queue, "mgget");

    if(fork() != 0) {
        if(fork() != 0) {
            sum_totals(queue);

            // Deallocate
            retcode = msgctl(queue, IPC_RMID, NULL);
            check_err(retcode, "msgctl");
        }
        else 
            analyzer(queue);
    }
    else {
        if(argc > 1)
            scanner(queue, argv[1], 0);
        else 
            scanner(queue, ".", 0);
    }
}