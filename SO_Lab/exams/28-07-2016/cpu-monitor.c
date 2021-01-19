/**
 * https://diraimondo.dmi.unict.it/wp-content/uploads/classes/so/lab-exams/?get=compito_2016-07-28.pdf
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/msg.h>

#define FILE_PATH "/proc/stat"
#define MAXLEN 2048
#define COLUMNS 60

typedef struct {
    long type;
    long int user;
    long int system;
    long int idle;
} raw;

typedef struct {
    long type;
    float user_perc;
    float system_perc;
} delta;


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

void sampler(int queue, int samples) {
    FILE* file;
    char line[MAXLEN];
    char* token = NULL;
    int retcode, len;
    raw msg;

    msg.type = 1;
    msg.user = 0;
    msg.system = 0;
    msg.idle = 0;

    
    for(int i=0; i<samples; i++) {
        // Open file to read 
        file = fopen(FILE_PATH, "r");
        check_ptr_err(file, "fopen");
        // Get the first row
        fgets(line, MAXLEN, file);
        len = strlen(line);
        
        if(line[len-1] == '\n')
            line[--len] = '\0';

        // Split by space to get user, system and idle
        token = strtok(line, " "); // This gets "cpu"

        msg.user = atoi(strtok(NULL, " "));
        strtok(NULL, " "); // This gets nice

        msg.system = atoi(strtok(NULL, " "));
        msg.idle = atoi(strtok(NULL, " "));
        fclose(file);

        retcode = msgsnd(queue, &msg, sizeof(msg) - sizeof(long), 0);
        check_err(retcode, "msgsnd sampler");

        if(i != samples-1)
            sleep(1);
    }

    exit(0);
}

void analyzer(int queue, int samples) {
    raw msg, prev_msg;
    delta result;
    int retcode;
    long int total_time = 0;

    // Init previous msg to -1
    prev_msg.user = -1;
    prev_msg.system = -1;
    prev_msg.idle = -1;

    result.type = 2;
    for(int i=0; i<samples; i++) {
        // Receive message #samples messages but sends #samples - 1
        retcode = msgrcv(queue, &msg, sizeof(msg), 1, 0);
        check_err(retcode, "msgrcv");

        if(prev_msg.user != -1) {
            total_time = (msg.user - prev_msg.user) + 
                         (msg.system - prev_msg.system) + 
                         (msg.idle - prev_msg.idle);
            
            result.user_perc = (float)(msg.user - prev_msg.user) / (float)(total_time);
            result.system_perc = (float)(msg.system - prev_msg.system) / (float)(total_time);

            // printf("\033[33;1mresult_u: %f\tresult_s: %f\033[0m\n", result.user_perc, result.system_perc);
            retcode = msgsnd(queue, &result, sizeof(result), 0);
            check_err(retcode, "msgsnd analyzer");
        }
        // Set previous message stats
        prev_msg.user = msg.user;
        prev_msg.system = msg.system;
        prev_msg.idle = msg.idle;
    }

    exit(0);
}

void print_chars(int n, char c) {
    for(int i=0; i<n; i++)
        putc(c, stdout);
}

void plotter(int queue, int samples) {
    delta result;
    int retcode, i;
    int user, system, idle;

    for(i=0; i<samples-1; i++) {
        // Receive message
        retcode = msgrcv(queue, &result, sizeof(result), 2, 0);
        check_err(retcode, "msgrcv");

        user = result.user_perc * COLUMNS;
        system = result.system_perc * COLUMNS;
        idle = COLUMNS - user - system;

        printf("\033[32;1m");
        print_chars(system, '#');
        printf("\033[35;1m");
        print_chars(user, '*');
        printf("\033[33;1m");
        print_chars(idle, '_');

        printf(" \033[32;1ms: %5.2f%%\t\033[35;1mu: %5.2f%%\033[0m\n", result.system_perc*100, result.user_perc*100);

        // printf("\033[31;1m%f\t%f\033[0m\n", result.user_perc, result.system_perc);    
    }
}

int main(int argc, char** argv) {
    int queue, samples, retcode;

    if(argc > 2) {
        printf("\033[31;1mUSE: %s [number-of-samples]\033[0m\n");
        exit(1);
    }

    if(argc == 2)
        samples = atoi(argv[1]);
    else
        samples = 30;

    // Create message queue
    queue = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0660);
    check_err(queue, "msgget");

    if(fork() != 0) {
        if(fork() != 0) {
            if(fork() != 0) {
                wait(NULL);
                wait(NULL);
                wait(NULL);

                // Deallocate queue
                retcode = msgctl(queue, IPC_RMID, NULL);
                check_err(retcode, "msgctl");
            }
            else
                plotter(queue, samples);
        }
        else
            analyzer(queue, samples);
    }
    else
        sampler(queue, samples);
}