/** 
 * Redirect stdout, stderror to file
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define LOGNAME "file.log"

int check_err(char* msg, int res) {
    if(res == -1) {
        perror(msg);
        exit(1);
    }

    return 0;
}

int main(int argc, char** argv) {
    int fd;

    // Try default stdou, stderr
    printf("Printed on default stdout\n");
    perror("Printed on default stderror\n");

    // Open log file
    fd = open(LOGNAME, O_WRONLY | O_CREAT | O_TRUNC, 0660);
    check_err("open", fd);

    // Redirect stdout
    close(STDOUT);
    dup(fd);
    printf("Printed on redirected stdout\n");
    perror("Printed on default stderror\n");

    // Redirect stderr
    close(STDERR);
    dup(fd);
    printf("Printed on redirected stdout\n");
    perror("Printed on redirected stderror\n");

    close(fd);  
}