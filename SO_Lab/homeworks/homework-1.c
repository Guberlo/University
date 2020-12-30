/*
    Homework n.1

    Scrivere un programma in linguaggio C che permetta di copiare un numero
    arbitrario di file regolari su una directory di destinazione preesistente.

    Il programma dovra' accettare una sintassi del tipo:
     $ homework-1 file1.txt path/file2.txt "nome con spazi.pdf" directory-destinazione
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <libgen.h>

#define MAXLEN 1024

int check_err(int value, char* msg) {
    if(value == -1) {
        perror(msg);
        exit(1);
    }

    return 0;
}

int main(int argc, char** argv) {
    int fd; // File descriptor
    int dd; // Destination file descriptor
    int read_code, write_code;
    char buffer[MAXLEN];
    char destination[MAXLEN];
    char* path;

    if(argc < 2) {
        printf("use: $ homework-1 file1.txt path/file2.txt \"nome con spazi.pdf\" directory-destinazione\n");
        exit(1);
    }

    printf("directory-destinazione: %s\n", argv[argc-1]);
    printf("basename of path: %s\n", __xpg_basename(argv[1]));

    for(int i=1; i< argc-1; i++) {
        path = strdup(argv[i]);
        path = __xpg_basename(path);

        fd = open(argv[i], O_RDONLY);
        check_err(fd, "open");

        memset(destination, 0, sizeof(destination));
        memset(buffer, 0, sizeof(buffer));
        strcpy(destination, argv[argc-1]);
        strcat(destination, path);
        printf("destination: %s\n", destination);

        dd = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0660);
        check_err(dd, "open destination");

        do
        {
            read_code = read(fd, buffer, sizeof(buffer));
            check_err(read_code, "read");

            write_code = write(dd, buffer, read_code);
            check_err(write_code, "write");
        } while (read_code > 0);
        
    }

    close(fd);
    close(dd);
}