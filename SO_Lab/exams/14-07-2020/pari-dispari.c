/**
 * https://diraimondo.dmi.unict.it/wp-content/uploads/classes/so/lab-exams/?get=compito_2020-07-14.pdf
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define MIN_PLAYER 2
#define MAX_PLAYER 6

typedef struct {
    long mtype;
    int mnumber;
} player_msg;

void check_err(int val, char* msg) {
    if(val == -1) {
        perror(msg);
        exit(1);
    }
}

void player(int queue, int p_num) {
    int number, retcode;
    char eog = 0;
    player_msg msg;

    /** I am using `getpid()*2` beacuse srand(time(NULL)) generates a seed once per second
     * If we remove the getpid, we'd get all the same values
     */
    srand(time(NULL) - getpid()*2);

    msg.mnumber = 0;

    while(msg.mnumber != -2) {
        // printf("\033[33;1mP-%d: RECEIVING MEX\033[0m\n", p_num);
        retcode = msgrcv(queue, &msg, sizeof(msg), p_num+10, 0);
        check_err(retcode, "msgrcv");

        // printf("\033[33;1mP-%d rcv: %d \033[0m\n", p_num, msg.mnumber);

        if(msg.mnumber == -2)
            break;

        if(msg.mnumber == -1) {
            msg.mnumber = rand() % 10;
            msg.mtype = p_num;

            printf("\033[33;1mP%d: %d\033[0m\n", p_num, msg.mnumber);
            retcode = msgsnd(queue, &msg, sizeof(msg), 0);
            check_err(retcode, "msgsnd");
        }
    }

    exit(0);
}

void judge_game(int queue, int p_number, int g_number) {
    int retcode, index, total_wins = 0, sum = 0;
    int numbers[p_number];
    int wins[p_number];
    char flag = 0;
    player_msg msg;

    // Init wins array
    for(int i=0; i<p_number; i++)
        wins[i] = 0;

    printf("\033[35;1m%d players\tqueue: %d\033[0m\n", p_number, queue);

    while(!flag) {
        // Send message to get number
        for(int i=1; i<p_number+1; i++) {
            msg.mtype = i+10;
            msg.mnumber = -1;
            
            retcode = msgsnd(queue, &msg, sizeof(msg), 0);
            check_err(retcode, "msgsnd father");
        }

        index = 0;
        // Receive numbers from children
        for(int i=1; i<p_number+1; i++) {
            retcode = msgrcv(queue, &msg, sizeof(msg), i, 0);
            check_err(retcode, "msgrcv");

            printf("\033[34;1mF: RECEIVED %d\n", msg.mnumber);
            numbers[index++] = msg.mnumber;
        }

        // Check if there are duplicates
        for(int i=0; i<p_number-1; i++) {
            for(int j=i+1; j<p_number; j++) {
                if(numbers[i] != numbers[j]) 
                    flag = 1;
                else {
                    flag = 0;
                    break;
                }
            }
            if(!flag)
                break;
        }

        if(flag) {
            total_wins++;

            // Sum players number and get the winner
            for(int i=0; i<p_number; i++) {
                sum += numbers[i];
            }
                
            printf("\033[35;1mGame-%d won by P%d\033[0m\n", total_wins, (sum % p_number));
            wins[sum%p_number]++;

            if(total_wins == g_number) 
                flag = 1;
            else
                flag = 0;
        }
    }

    // Send EOG
    msg.mnumber = -2;
    for(int i=1; i<p_number+1; i++) {
        msg.mtype = i+10;
        
        retcode = msgsnd(queue, &msg, sizeof(msg), 0);
        check_err(retcode, "msgsnd");
    }

    int max = -1;
    int winner = -1;
    for(int i=0; i<p_number; i++) {
        if(wins[i] > max) {
            max = wins[i];
            winner = i;
        }
    }

    printf("\033[35;1mThe overall winner, counting %d vicotries is: . . . . . P%d!!\033[0m\n", wins[winner], winner);
}

int main(int argc, char** argv) {
    int queue, retcode;
    int p_number, g_number;

    if(argc != 3) {
        printf("\033[31;1mUSE: %s <n=player-number> <m=game-number>\033[0m\n");
        exit(1);
    }

    // Check input 
    p_number = atoi(argv[1] + 2);
    if(p_number < MIN_PLAYER || p_number > MAX_PLAYER) {
        printf("\033[31;1mERROR: MIN_PLAYER: %d, MAX_PLAYER: %d\033[0m\n", MIN_PLAYER, MAX_PLAYER);
        exit(1);
    }

    g_number = atoi(argv[2] + 2);
    if(g_number < 1) {
        printf("\033[31;1mERROR: give at least 1 number of games\033[0m\n");
        exit(1);
    }

    // Create msg queue
    queue = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0660);
    check_err(queue, "msgget");

    for(int i=1; i<p_number+1; i++) {
        if(fork() == 0)
            player(queue, i);
    }

    judge_game(queue, p_number, g_number);

    for(int i=0; i<p_number; i++)
        wait(NULL);

    // Deallocate queue
    retcode = msgctl(queue, IPC_RMID, NULL);
    check_err(retcode, "msgctl");
}