#include <stdio.h>
#include <stdlib.h>

int check_err(char* msg, int res) {
    if(res == -1) {
        perror(msg);
        exit(1);
    }

    return 0;
}