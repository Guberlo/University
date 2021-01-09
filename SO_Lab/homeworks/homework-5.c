/*
    Homework n.5

    Estendere l'esempio 'nanoshell.c' ad una shell piu' realistica in cui
    si possono:
    - passare argomenti al comando invocato (per semplicita', assumiamo
    che questi non contengano spazi);
    - usare la redirezione dei canali di input/output/error;
    - mandare un comando in esecuzione in background (con la '&' finale).

    Esempi di invocazione che la shell dovrebbe supportare sono:
    $ cal 3 2015
    $ cp /etc/passwd /etc/hosts /tmp
    $ cat </dev/passwd >/tmp/passwd
    $ cat filechenonesiste 2>/dev/null
    $ ls -R /etc/ &
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAXLEN 2048
#define MAXARGS 8

#define STDIN 0
#define STDOUT 1
#define STDERR 2

void check_err(int value, char *msg)
{
    if (value == -1)
    {
        perror(msg);
        exit(1);
    }
}

int main(int argc, char **argv)
{
    char buffer[MAXLEN];
    char *args[MAXARGS];
    char *token;
    char *new_stdin, *new_stdout, *new_stderr;
    int len, pid, fd;
    int i, bg = 0;

    while (1)
    {
        // Get input command
        printf("\033[35;1m$ \033[0m");
        fgets(buffer, MAXLEN, stdin);

        len = strlen(buffer);
        if (buffer[len - 1] == '\n')
            buffer[--len] = '\0';

        token = strtok(buffer, " ");
        if (token == NULL)
        {
            printf("\033[31;1mMalformed command!\033[0m\n");
            continue;
        }

        do
        {
            // Check if background execution
            if (strlen(token) == 1 && token[0] == '&')
            {
                bg = 1;
                continue;
            }

            // Check if channel redirection
            if (strlen(token) == 1 && token[0] == '<')
            {
                if (new_stdin == NULL)
                {
                    // Get the name of the file (token + 1 = token[i+1])
                    new_stdin = strdup(token + 1);
                    if (!access(new_stdin, R_OK))
                    {
                        printf("\033[31;1mImpossible to access %s\033[0m\n", new_stdin);
                        free(new_stdin);
                        continue;
                    }
                }
                else
                {
                    printf("\033[31;1mSTDIN has already been duplicated!\033[0m\n");
                    continue;
                }
                continue;
            }
            else if (strlen(token) == 1 && token[0] == '2')
            {
                if (token[1] == '>')
                {
                    if (new_stderr == NULL)
                    {
                        new_stderr = strdup(token + 2);
                        if (!access(new_stderr, R_OK))
                        {
                            printf("\033[31;1mImpossible to access %s\033[0m\n", new_stderr);
                            free(new_stderr);
                            continue;
                        }
                    }
                    else
                    {
                        printf("\033[31;1mSTDERR has already been duplicated!\033[0m\n");
                        continue;
                    }
                }
                else {
                    if(new_stdout == NULL) {
                        new_stdout = strdup(token + 1);
                        if(!access(new_stdout, R_OK)) {
                            printf("\033[31;1mImpossible to access %s\033[0m\n", new_stderr);
                            free(new_stderr);
                            continue;
                        }
                    }
                    else {
                        printf("\033[31;1mSTDOUT has already been duplicated!\033[0m\n");
                        continue;
                    }
                }
                continue;
            }
            args[i++] = strdup(token);
        }while ((token = strtok(NULL, " ")) != NULL);
        args[i] = NULL;

        pid = fork();
        check_err(pid, "fork");

        if(pid == 0) {
            if(new_stdin != NULL) {
                fd = open(new_stdin, O_RDONLY);
                check_err(fd, "openstdin");
                close(STDIN);
                dup(fd);
            }
            if(new_stdout != NULL) {
                fd = open(new_stdout, O_WRONLY | O_CREAT | O_TRUNC, 0666);
                check_err(fd, "openstdout");
                close(STDOUT);
                dup(fd);
            }
            if(new_stdin != NULL) {
                fd = open(new_stderr, O_WRONLY | O_CREAT | O_TRUNC, 0666);
                check_err(fd, "openstderr");
                close(STDERR);
                dup(fd);
            }

            execvp(args[0], args);
            fprintf(stderr, "Error with exec command: %s", args[0]);
        } else if(!bg) 
            wait(NULL);

        // Free memory
        if (new_stdin != NULL) free(new_stdin);
        if (new_stderr != NULL) free(new_stderr);
        if (new_stdout != NULL) free(new_stdout);
        i = 0;
        while (args[i] != NULL)
            free(args[i++]);
    }

}
