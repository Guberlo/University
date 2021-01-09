/**
 * Read from a file
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define MAXBUF 256

int check_err(char* msg, int res) {
    if(retcode == -1) {
        perror(msg);
        exit(1);
    }

    return 0;
}

int main(int argc, char** argv) {
    int fd; // File descriptor
    char buffer[MAXBUF]; // Buffer to read file
    int retcode;

    fd = open("asd.txt", O_RDONLY);
    check_err("open", fd);

    retcode = read(fd, &buffer, sizeof(buffer) - 1);
    check_err("read", retcode);

    buffer[retcode] = '\0'; // Null byte alla fine della stringa

    printf("Read from file: \n");
    printf("%s\n", buffer);

    close(fd);

}