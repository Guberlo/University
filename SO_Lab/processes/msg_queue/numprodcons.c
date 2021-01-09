/**
 * The program can be executed as sender or receiver.
 * The code is in one file just for semplicity.
 * 
 * 
 * USE > numprodcons R1: for receiver of numbers of type 1
 * USE > numprodcons R2: for receiver of numbers of type 2
 * USE > numprodcons S: for sender
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>

#define MAXMESSAGES 5000
#define TYPE_A 1
#define TYPE_B 2
#define EOFN -1

typedef long numtype;

typedef struct {
    long mtype;
    numtype mnum;
}msg;

void check_err(int val, char* msg) {
    if(val == -1) {
        perror(msg);
        exit(1);
    }
}

void sender(int queue) {
    msg mex;
    numtype num;
    int type, retcode;
    long a_sum, b_sum;

    for(int i=0; i<MAXMESSAGES; i++) {
        // Generate a random number
        num = rand() % 124123;
        // Generate a random type [number between 1 and 2]
        type = rand() % 2 + TYPE_A;

        // Set information into msg
        mex.mnum = num;
        mex.mtype = type;

        // Send message
        retcode = msgsnd(queue, &mex, sizeof(mex.mnum), 0);
        check_err(retcode, "msgsnd");

        // Do a strange operation idk why
        if(type == TYPE_A)
            a_sum += num;
        else
            b_sum += num;

        // Show some recap message
        printf("\033[36;1mMessage no.%d: num=%3lu\ttype=%d\ta_sum=%3lu\tb_sum=%3lu\033[0m\n", i, num, type, a_sum, b_sum);

        // Add even a strange random sleep
        //usleep(1000 + rand() % 4000);
    }

    // Send an EOFN to each of the receivers
    mex.mnum = EOFN;

    mex.mtype = TYPE_A;
    retcode = msgsnd(queue, &mex, sizeof(mex.mnum), 0);
    check_err(retcode, "msgsnd type_a");

    mex.mtype = TYPE_B;
    retcode = msgsnd(queue, &mex, sizeof(mex.mnum), 0);
    check_err(retcode, "msgsnd type_a");

    // Delete queue if needed
    printf("\033[31;1mPRESS A KEY IF YOU WANT TO DELETE THE QUEUE...\033[0m\n");
    fgetc(stdin);
    msgctl(queue, IPC_RMID, NULL);
}

void receiver(int queue, int type) {
    int retcode, i = 0;
    long sum = 0;
    msg mex;

    mex.mnum = 0; // To avoid problems with EOFN check at the start of the program

    printf("\033[33;1mR%d STARTED\033[0m\n",type);

    while(mex.mnum != EOFN) {
        retcode = msgrcv(queue, &mex, sizeof(mex.mnum), type, 0);
        check_err(retcode, "msgrcv");

        if(mex.mnum == EOFN)
            break;
        
        sum += mex.mnum;

        printf("\033[33;1mMessage no.%d: num=%3lu tipo=%d sum=%8lu\033[0m\n", i, mex.mnum, type, sum);
        i++;
    }
}

int main(int argc, char** argv) {
    int queue_fd;
    key_t key = 124;

    if(argc != 2) {
        printf("\033[31;1mUSE: %s S or R1 or R2\033[0m\n", argv[0]);
        exit(1);
    }

    // Create queue
    queue_fd = msgget(key, IPC_CREAT | 0660);
    check_err(queue_fd, "msget");

    if(argv[1][0] == 'S') 
        // Sender
        sender(queue_fd);
    else {
        if(argv[1][1] == '1')
            receiver(queue_fd, TYPE_A);
        else if(argv[1][1] == '2')
            receiver(queue_fd, TYPE_B);
        else 
            printf("\033[31;1mFUCK YOU WRONG USAGE\033[0m\n"); exit(1);
    }
}