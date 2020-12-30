/**
 * Copies a file using only read and write
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
    int s_fd; // File descriptor sorgente
    int d_fd; // File descriptor destinatazione
    char buffer[MAXLEN];
    int read_code;
    int write_code;

    if(argc != 3) {
        printf("use: %s <sorgente> <destinazione>\n", argv[0]);
        exit(1);
    }

    // Copy the content of s into the buffer
    s_fd = open(argv[1], O_RDONLY);
    check_err("open s_fd", s_fd);

    d_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0660);
    check_err("open d_fd", d_fd);

    do {
        // Read from file
        read_code = read(s_fd, &buffer, sizeof(buffer));
        check_err("read", read_code);

        printf("%d byte read \n", read_code);

        // Write from buffer to file
        write_code = write(d_fd, &buffer, read_code);
        check_err("write" , d_fd);

        printf("%s\n", buffer);
    } while(read_code > 0);

    close(s_fd);
    close(d_fd);

}