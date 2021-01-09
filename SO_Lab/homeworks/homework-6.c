/*
    Homework n.6

    Scrivere un programma che crei un processo figlio con cui scambiera' dati
    tramite una coda di messaggi. Tale coda sara' creata dal padre e distrutta,
    a fine lavori, dal figlio.

    Il processo padre dovra' accettare comandi inseriti da tastiera (per semplicita'
    senza parametri) e questi dovranno essere inviati al figlio che li eseguira'
    di volta in volta creando dei processi nipoti: uno per ogni comando.

    Il tutto si dovra' arrestare correttamente all'inserimento del comando
    'exit' sul padre.

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/msg.h>

#define MAXLEN 1024

typedef struct {
    long mtype;
    char mtext[MAXLEN];
} msg;

void check_err(int val, char* msg) {
    if(val == -1) {
        perror(msg);
        exit(1);
    }
}

void get_commands(int queue_fd) {
    msg command;
    int len, retcode;

    command.mtype = 1;

    while(strcmp(command.mtext, "exit") != 0) {
        printf("\033[34;1m$ \033[0m");
        fgets(command.mtext, MAXLEN, stdin);

        len = strlen(command.mtext);
        if(command.mtext[len - 1] == '\n')
            command.mtext[--len] = '\0';
        
        retcode = msgsnd(queue_fd, &command, len + 1, 0);
        check_err(retcode, "msgsnd");
    }
}

void execute_command(int queue_fd) {
    msg command;
    int retcode;

    while(strcmp(command.mtext, "exit") != 0) {
        retcode = msgrcv(queue_fd, &command, MAXLEN, 0, 0);
        check_err(retcode, "msgrcv");

        if(strcmp(command.mtext, "exit") == 0) {
            break;
        }

        if(fork() == 0) {
            execlp(command.mtext, command.mtext, NULL);
            perror("execlp");

            retcode = msgctl(queue_fd, IPC_RMID, NULL);
            check_err(retcode, "msgctl");
            
            exit(1);
        }

        printf("\033[36;1mRECEIVED: %s\033[0m\n", command.mtext);
    }

    retcode = msgctl(queue_fd, IPC_RMID, NULL);
    check_err(retcode, "msgctl");

    exit(0);
}

int main(int argc, char** argv) {
    int queue_fd;

    // Create queue
    queue_fd = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0660);
    check_err(queue_fd, "msgget");

    if(fork() != 0) {
        get_commands(queue_fd);
    } 
    else
        execute_command(queue_fd);
}