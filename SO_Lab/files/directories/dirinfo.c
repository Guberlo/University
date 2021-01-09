#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>

void check_err(int value, char* msg) {
    if(value == -1) {
        perror(msg);
        exit(1);
    }
}

void check_dir_err(DIR*  value, char* msg) {
    if(value == NULL) {
        perror(msg);
        exit(1);
    }
}

int main(int argc, char** argv) {
    DIR* dir_stream;
    struct dirent* dir;
    int retcode;

    if(argc != 2) {
        printf("\033[31;1m use: dirinfo <path_to_dir>\033[0m\n");
        exit(1);
    }

    dir_stream = opendir(argv[1]);
    check_dir_err(dir_stream, "open dir");

    while((dir = readdir(dir_stream)) != NULL) {
        printf("\033[33;1mReading file: %s\033[0m\n", dir->d_name);
    }

    closedir(dir_stream);

}