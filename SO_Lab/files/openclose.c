/**
 * Simply opens and closes a file
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv) {
    int fd; // File descriptor

    fd = open("open.txt", O_RDWR | O_CREAT);
    if( fd == -1) {
        perror("open");
        exit(1);
    }

    printf("File %s opened with file descriptor: %d", "open.txt", fd);

    close(fd);

    printf("\nFile closed.");
    
}