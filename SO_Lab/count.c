/**
 * Count how big a file is using only read
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define MAXLEN 1024

int check_err(char* msg, int res) {
    if(res == -1) {
        perror(msg);
        exit(1);
    }

    return 0;
}

int main(int argc, char** argv) {
    int fd; // File description
    char buffer[MAXLEN];
    int retcode;
    int total_size = 0;

    if(argc != 2) {
        printf("Give as an argument also the filename!\n");
        exit(1);
    }

    fd = open(argv[1], O_RDONLY);
    check_err("open", fd);

    while( (retcode = read(fd, &buffer, sizeof(buffer) ) > 0)) {
        check_err("read", retcode);
        total_size += retcode;
    }

    printf("This is the total size of the file: %d byte\n", total_size);

    close(fd);
}