/**
 * Implement mv using only link() and unlink()
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int check_err(int code, char* msg) {
    if(code == -1) {
        perror(msg);
        exit(1);
    }
}

int main(int argc, char** argv) {
    int retcode;

    if(argc != 3) {
        printf("\033[31;1m ERROR use: move <file_to_move> <destination> \033[0m\n");
        exit(1);
    }

    // Link file to new destination
    retcode = link(argv[1], argv[2]);
    check_err(retcode, "link");

    // Unlink the original file in order to remove it
    retcode = unlink(argv[1]);
    check_err(retcode, "unlink");

    printf("\033[33;1m SUCCESS: %s has been succesfully moved to %s \033[0m\n", argv[1], argv[2]);
}