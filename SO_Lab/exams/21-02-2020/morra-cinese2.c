/**
 * https://diraimondo.dmi.unict.it/wp-content/uploads/classes/so/lab-exams/?get=compito_2020-02-21.pdf
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

#define FIFO_PATH "/tmp/my-fifo.fifo"
#define MAX_MOVES 3

#define P_ONE 1
#define P_TWO 2

#define MAX_PLAYERS 2

char moves[MAX_MOVES] = {'S', 'C', 'F'};

typedef struct {
    long mtype;
    char move;
} player_msg;

void check_err(int val, char* msg) {
    if(val == -1) {
        perror(msg);
        exit(1);
    }
}

void player(int queue, int p_num) {
    int retcode;
    player_msg msg;

    srand(time(NULL) ^ getpid() * 18);

    msg.move = 0;
    while(msg.move != '8') {
        // Receive msg !!! P_NUM + 5 in order to listen to the proper msg, otherwise problem with father !!!!!
        retcode = msgrcv(queue, &msg, sizeof(msg), p_num + 5, 0);
        check_err(retcode, "msgrcv");

        if(msg.move == '8')
            break;

        // Refree sends -1 when we need to make a choice
        int index = rand() % MAX_MOVES;
        if(msg.move == '9') {
            msg.mtype = p_num;
            msg.move = moves[index];
            printf("\033[33;1mP%d: %c\033[0m\n", p_num, msg.move);
            // Send msg to refree
            retcode = msgsnd(queue, &msg, sizeof(msg), 0);
            check_err(retcode, "msgsnd choice");
        }
    }

    exit(0);
}

char announce_winner(char p_one, char p_two) {
    if(p_one == 'S')
        return p_two == 'C' ? '2' : '1';

    if(p_one == 'F')
        return p_two == 'S' ? '2' : '1';

    if(p_one == 'C')
        return p_two == 'F' ? '2' : '1';
}

void refree(int queue, int g_number) {
    int retcode, total_games = 0, fd, index;
    char winner, flag = 0;
    char* players_moves;
    player_msg msg;

    fd = open(FIFO_PATH, O_WRONLY);
    check_err(fd, "open w");

    players_moves = malloc(sizeof(char) * MAX_PLAYERS);
    while(1) {
        // Ask players to choose sending -1
        msg.move = '9';
        for(int i=1; i<MAX_PLAYERS+1; i++) {
            msg.mtype = i + 5;
            retcode = msgsnd(queue, &msg, sizeof(msg), 0);
            check_err(retcode, "msgsnd refree ask");
        }

        index = 0;
        // Receive moves from children
        for(int i=1; i<MAX_PLAYERS+1; i++) {
            retcode = msgrcv(queue, &msg, sizeof(msg), i, 0);
            check_err(retcode, "msgrcv");

            players_moves[index++] = msg.move;
        }

        if(players_moves[0] != players_moves[1]) {
            flag = 1;
            winner = announce_winner(players_moves[0], players_moves[1]);
            printf("\033[34;1mROUND WINNER IS: P%c\033[0m\n", winner);
            retcode = write(fd, &winner, 1);
            check_err(retcode, "write");
            total_games++;
        }
        else {
            flag = 0;
            printf("\033[34;1mDRAW\033[0m\n");
        }
        
        if(flag && total_games == g_number)
            break;
    }

    // Send EOF
    msg.move = '8';
    for(int i=1; i<MAX_PLAYERS+1; i++) {
        msg.mtype = i+5;
        retcode = msgsnd(queue, &msg, sizeof(msg), 0);
        check_err(retcode, "msgsnd  eof");
    }

    close(fd);
}

void score() {
    int retcode, fd;
    int wins[MAX_PLAYERS] = {0};
    char winner;

    sleep(0.5);
    
    fd = open(FIFO_PATH, O_RDONLY);
    check_err(fd, "open");

    while(read(fd, &winner, 1) > 0) {
        wins[(winner - '0') - 1]++;
        printf("\033[35;1mP%c has %d wins\033[0m\n", winner, wins[(winner - '0') - 1]);
    }

    close(fd);

    printf("\033[35;1mLEADERBOARD: P1: %d\t P2: %d\033[0m\n", wins[0], wins[1]);

    if(wins[0] == wins[1])
        printf("\033[34;1mDRAW: both player have %d wins.\033[0m\n", wins[0]);
    else if(wins[0] > wins[1])
        printf("\033[31;1m Player 1 won with %d wins\033[0m\n", wins[0]);
    else 
        printf("\033[34;1mPlayer 2 won with %d victories\033[0m\n", wins[1]);

    exit(0);
}

int main(int argc, char** argv) {
    int queue, p_fd, retcode;

    if(argc != 2) {
        printf("\033[31;1mUSE: %s <game-number>\033[0m\n", argv[0]);
        exit(1);
    }

    // Create queue
    queue = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0660);
    check_err(queue, "msgget");

    // Create named pipe
    retcode = mkfifo(FIFO_PATH, 0660);
    check_err(retcode, "mkfifo");

    // Create children
    if(fork() != 0) {
        if(fork() != 0) {
            if(fork() != 0) {
                if(fork() != 0) {
                    wait(NULL);
                    wait(NULL);
                    wait(NULL);
                    wait(NULL);

                    // Deallocate and unlink
                    retcode = msgctl(queue, IPC_RMID, NULL);
                    check_err(retcode, "msgctl");

                    unlink(FIFO_PATH);
                }
                else
                    score();
            }
            else 
                refree(queue, atoi(argv[1]));
        }
        else 
            player(queue, P_TWO);
    }
    else 
        player(queue, P_ONE);
}