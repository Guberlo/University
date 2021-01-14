/*
    Homework n.7

    Modificare l'homework precedente (n.6) facendo in modo che il figlio che
    riceve il comando da eseguire tramite la coda, catturi lo standard output
    e lo standard error del figlio nipote usando la redirezione su pipe tra
    processi. L'output catturato dovrà essere mandato indietro al padre
    tramite un messaggio (per semplicita', assumiamo sufficiente grande).
    Tale contenuto sara' poi visualizzato sul terminale dal padre.

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
    msg command, output;
    int retcode, len;

    command.mtype = 1;

    while(strcmp(command.mtext, "quit") != 0) {
        printf("\033[34;1m$ \033[0m");
        // Get input and remove \n
        fgets(command.mtext, MAXLEN, stdin);
        len = strlen(command.mtext);

        if(command.mtext[len - 1] == '\n')
            command.mtext[--len] = '\0';
        
        if(strcmp(command.mtext, "quit") == 0)
            break;

        // Send message
        retcode = msgsnd(queue_fd, &command, len + 1, 0);
        check_err(retcode, "msgsnd G.C");

        // Receive output from child
        retcode = msgrcv(queue_fd, &output, MAXLEN, 0, 0);
        check_err(retcode, "msgrcv G.C");

        printf("REDIRECT: %s", output.mtext);
    }
}

void execute_commands(int queue_fd) {
    msg command, output;
    int retcode;
    int pipe_fd[2];

    while(strcmp(command.mtext, "quit") != 0) {
        // Receive command from father
        retcode = msgrcv(queue_fd, &command, MAXLEN, 0, 0);
        printf("\033[31;1mDEBUG: msgrcv->%s\033[0m\n", command.mtext);
        check_err(retcode, "msgrcv E.C RCV");

        if(strcmp(command.mtext, "quit") == 0)
            break;

        // Create pipe
        retcode = pipe(pipe_fd);
        check_err(retcode, "pipe");

        // Create child to execute command
        if(fork() == 0) {
            // Redirect stdout and stderr to pipe
            close(STDOUT_FILENO);
            dup(pipe_fd[1]);
            close(STDERR_FILENO);
            dup(pipe_fd[1]);

            execlp(command.mtext, command.mtext, NULL);
            perror("execlp");
            exit(1);
        }
        // Close not used pipe channel
        close(pipe_fd[1]);

        // Read returned output from child
        retcode = read(pipe_fd[0], output.mtext, MAXLEN - 1);
        check_err(retcode, "read");
        output.mtext[retcode] = '\0';
        output.mtype = 1;

        // Send output to be displayed in father
        retcode = msgsnd(queue_fd, &output, strlen(output.mtext) + 1, 0);
        check_err(retcode, "msgsnd E.C SND");

        printf("\033[36;1mRECEIVED COMMAND: %s \033[0m\n", command.mtext);

        close(pipe_fd[0]);
    }

    retcode = msgctl(queue_fd, IPC_RMID, NULL);
    check_err(retcode, "msgctl");
}

int main(int argc, char** argv) {
    int queue_fd;

    if(argc > 1) {
        printf("\033[31;1mUSE: %s\033[0m\n", argv[0]);
        exit(1);
    }

    // Crete msg queue
    queue_fd = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0660);
    check_err(queue_fd, "msgget");

    if(fork() != 0)
        get_commands(queue_fd);
    else
        execute_commands(queue_fd);
}