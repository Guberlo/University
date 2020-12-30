/*
    Homework n.2

    Estendere l'esempio 'move.c' visto a lezione per supportare i 2 casi speciali:
    - spostamento cross-filesystem: individuato tale caso, il file deve essere
      spostato utilizzando la strategia "copia & cancella";
    - spostamento di un link simbolico: individuato tale caso, il link simbolico
      deve essere ricreato a destinazione con lo stesso contenuto (ovvero il percorso
      che denota l'oggetto referenziato); notate come tale spostamento potrebbe
      rendere il nuovo link simbolico non effettivamente valido.

    La sintassi da supportare e' la seguente:
     $ homework-2 <pathname sorgente> <pathname destinazione>
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <libgen.h>

#define MAXLEN 2048

void check_err(int value, char *msg)
{
    if (value == -1)
    {
        perror(msg);
        exit(-1);
    }
}

int main(int argc, char **argv)
{
    struct stat statbuff, statbuff2;
    char linkpath[MAXLEN];
    char buffer[MAXLEN];
    char dstdir[MAXLEN];
    int retcode, readcode;
    int sd, dd;

    if (argc != 3)
    {
        printf("\033[31;1m utilizzo: homework-2 <pathname sorgente> <pathname destinazione>\033[0m\n");
        exit(-1);
    }

    // Check file type
    retcode = lstat(argv[1], &statbuff);
    check_err(retcode, "lstat");

    if (S_ISLNK(statbuff.st_mode))
    {
        printf("\033[33;1m Moving symlink!\033[0m\n");
        // Read link path
        retcode = readlink(argv[1], linkpath, MAXLEN - 1);
        check_err(retcode, "readlink");
        linkpath[retcode] = '\0';

        // Create a new symlink from the path to new destination
        retcode = symlink(linkpath, argv[2]);
        check_err(retcode, "symlink");
    }
    else if (S_ISREG(statbuff.st_mode))
    {
        // Get parent directory stats. Needed to make a correct comparison
        // Because if the file already exists (firts open and then read stat)
        // Will cause a problem when creating an hard link
        strncpy(dstdir, argv[2], MAXLEN);
        strcpy(dstdir, dirname(dstdir));
        retcode = stat(dstdir, &statbuff2);
        check_err(retcode, "lstat2");

        if (statbuff.st_dev != statbuff2.st_dev)
        {
            printf("\033[33;1m Moving from one fs to another: %d -> %d\033[0m\n", statbuff.st_dev, statbuff2.st_dev);
            // Read content and write to new file

            sd = open(argv[1], O_RDONLY);
            check_err(sd, "open1");
            dd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, statbuff.st_mode & 0777);
            check_err(dd, "open2");

            do
            {
                readcode = read(sd, buffer, MAXLEN);
                check_err(readcode, "read");

                retcode = write(dd, buffer, readcode);
                check_err(retcode, "write");
            } while (readcode > 0);

            close(sd);
        }
        else
        {
            printf("\033[33;1m Making an hard link\033[0m\n");
            retcode = link(argv[1], argv[2]);
            check_err(retcode, "link");
        }

        close(dd);
    }

    // Remove previous file
    retcode = unlink(argv[1]);
    check_err(retcode, "unlink");

    printf("\033[33;1m SUCCESS: %s has been succesfully moved to %s \033[0m\n", argv[1], argv[2]);
}