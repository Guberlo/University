#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

void check_err(int value, char* msg) {
    if(value == -1) {
        perror(msg);
        exit(1);
    }
}

void check_dir_err(DIR* dir) {
    if(dir == NULL) {
        perror("opendir");
        exit(1);
    }
}

void printdir(char* dir_name, int space_counter) {
    DIR* dir_stream;
    struct dirent* dir;
    struct stat stat_buff;
    int retcode;

    // Open directory
    dir_stream = opendir(dir_name);
    check_dir_err(dir_stream);

    // Change working directory to semplify ops
    retcode = chdir(dir_name);
    check_err(retcode, "chdir");

    while( (dir = readdir(dir_stream)) != NULL) {
        // Get file stats
        lstat(dir->d_name, &stat_buff);

        // Check file type

        // Check subdirectories
        if(S_ISDIR(stat_buff.st_mode)) {
            // Avoid looping with . and ..
            if(strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
                continue;
            
            printf("%*s", space_counter * 4, " ");
            printf("\033[35;1m%s/\033[0m\n", dir->d_name);

            // Recursively call on subdirectories
            printdir(dir->d_name, space_counter + 1);
        }
        else {
            printf("%*s", space_counter * 4, " ");
            printf("\033[33;1m%s\033[0m\n", dir->d_name);
        }
    }
    chdir("..");

    closedir(dir_stream);
}

int main(int argc, char** argv) {
    char* path;

    if(argc > 2) {
        printf("\033[31;1m use: dirlist OR dirlist <path>\033[0m\n");
        exit(1);
    }

    if(argc == 1) 
        path = ".";
    else 
        path = argv[1];

    printdir(path, 0);

}