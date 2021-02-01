/**
 * https://diraimondo.dmi.unict.it/wp-content/uploads/classes/so/lab-exams/?get=compito_2020-01-29.pdf
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define P1 0
#define P2 1
#define JUDGE 2
#define SCORE 3
#define START_GAME 4

const char choices[3] = {'S', 'C', 'F'};

typedef struct {
    char p1_move;
    char p2_move;
    char winner;
    char eof;
} message;

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

int WAIT(int sem, int sem_num) {
    struct sembuf WAIT[1] = {sem_num, -1, 0};
    return semop(sem, WAIT, 1);
}

int SIGNAL(int sem, int sem_num) {
    struct sembuf SIGNAL[1] = {sem_num, +1, 0};
    return semop(sem, SIGNAL, 1);
}

char check_winner(char p1_move, char p2_move) {
    if(p1_move == 'S' && p2_move != 'S')
        return p2_move == 'F' ? '1' : '2';
    if(p1_move == 'F' && p2_move != 'F')
        return p2_move == 'C' ? '1' : '2';
    if(p1_move == 'C' && p2_move != 'C')
        return p2_move == 'S' ? '1' : '2';
    
    return '0';
}

void judge(int shm, int sem, int g_number) {
    message* game_message;
    int total_games = 0;
    char winner;

    // Attach shm
    game_message = shmat(shm, NULL, 0);
    check_ptr_err(game_message, "shmat");

    // No need to wait since other processes wait
    game_message->eof = 0;

    while(1) {
        WAIT(sem, START_GAME);
        SIGNAL(sem, P1);
        SIGNAL(sem, P2);
        WAIT(sem, JUDGE);
        WAIT(sem, JUDGE);
        if(total_games == g_number) {
            // SET EOF to 1 and signal players and score
            game_message->eof = 1;
            SIGNAL(sem, P1);
            SIGNAL(sem, P2);
            SIGNAL(sem, SCORE);
            break;
        }

        printf("\033[34;1mP1: %c\tP2: %c\033[0m\n", game_message->p1_move, game_message->p2_move);
        winner = check_winner(game_message->p1_move, game_message->p2_move);
        if(winner == '0')
            SIGNAL(sem, START_GAME);
        else {
            printf("\033[36;1mROUND WINNER: P%c\033[0m\n", winner);
            game_message->winner = winner;
            total_games++;
            SIGNAL(sem, SCORE);
        }
    }
    exit(0);
}

void player(int shm, int sem, int p_index) {
    message* game_message;

    srand(time(NULL) ^ getpid() * 18);

    // Attach to shm
    game_message = shmat(shm, NULL, 0);
    check_ptr_err(game_message, "shmat");

    while(1) {
        WAIT(sem, p_index);
        if(game_message->eof == 1) {
            break;
        }
        if(p_index == 0)
            game_message->p1_move = choices[rand() % 3];
        else
            game_message->p2_move = choices[rand() % 3];
        SIGNAL(sem, JUDGE);
    }

    exit(0);
}

void score(int shm, int sem) {
    message* game_message;
    int score[2] = {0};
    int index, winner;

    // Attach to shm
    game_message = shmat(shm, NULL, 0);
    check_ptr_err(game_message, "shmat");

    while(1) {
        WAIT(sem, SCORE);
        if(game_message->eof == 1)
            break;
        index = (game_message->winner - '0') - 1;
        score[index]++;
        SIGNAL(sem, START_GAME);
    }
    // Get leaderboard
    if(score[0] > score[1]) {
        winner = score[0];
        printf("\033[35;1mP%d WON THE TOURNAMENT!\nP1 has %d wins, P2 has %d wins.\033[0m\n", 1, score[0], score[1]);
    }
    else if(score[0] < score[1]) {
        winner = score[1];
        printf("\033[35;1mP%d WON THE TOURNAMENT!\nP1 has %d wins, P2 has %d wins.\033[0m\n", 2, score[0], score[1]);
    }
    else
        printf("\033[35;1mDRAW: both of the players have %d wins.\033[0m\n", score[1]);
}

int main(int argc, char** argv) {
    int shm, sem, g_number, retcode;

    if(argc != 2) {
        printf("\033[31;1mUSE: %s <game-number>\033[0m\n", argv[0]);
        exit(1);
    }

    g_number = atoi(argv[1]);
    if(g_number == 0) {
        printf("\033[31;1mERROR: %s is not valid parameter. Insert a number\033[0m\n");
        exit(1);
    }

    // Create shm
    shm = shmget(IPC_PRIVATE, sizeof(message), IPC_CREAT | IPC_EXCL | 0660);
    check_err(shm, "shmget");

    // Create sem
    sem = semget(IPC_PRIVATE, 5, IPC_CREAT | IPC_EXCL | 0660);
    check_err(sem, "semget");

    // Init sems
    retcode = semctl(sem, P1, SETVAL, 0);
    check_err(retcode, "semctl");

    retcode = semctl(sem, P2, SETVAL, 0);
    check_err(retcode, "semctl");

    retcode = semctl(sem, JUDGE, SETVAL, 0);
    check_err(retcode, "semctl");

    retcode = semctl(sem, SCORE, SETVAL, 0);
    check_err(retcode, "semctl");

    retcode = semctl(sem, START_GAME, SETVAL, 1);
    check_err(retcode, "semctl");

    if(fork() != 0) {
        if(fork() != 0) {
            if(fork() != 0) {
                if(fork() != 0) {
                    wait(NULL);
                    wait(NULL);
                    wait(NULL);
                    wait(NULL);

                    // Deallocate shm and sem
                    retcode = shmctl(shm, IPC_RMID, NULL);
                    check_err(retcode, "shmctl");

                    retcode = semctl(sem, 0, IPC_RMID);
                    check_err(retcode, "semctl");
                }
                else
                    score(shm, sem);
            }
            else
                judge(shm, sem, g_number);
        }
        else
            player(shm, sem, P2);
    }
    else 
        player(shm, sem, P1);
}