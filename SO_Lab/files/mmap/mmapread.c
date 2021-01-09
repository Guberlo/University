#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

void check_err(int value, char* msg) {
    if(value == -1) {
        perror(msg);
        exit(1);
    }
}

void check_map_err(void*  value, char* msg) {
    if(value == MAP_FAILED) {
        perror(msg);
        exit(1);
    }
}

int main(int argc, char** argv) {
    int fd;
    int retcode;
    struct stat stat_buf;
    char* map_data;

    if(argc < 2) {
        printf("\033[31;1m use: mmapread  <file>");
        exit(1);
    }

    // Open file
    fd = open(argv[1], O_RDONLY);
    check_err(fd, "open");

    // Get file stat to know dimension
    retcode = fstat(fd, &stat_buf);
    check_err(retcode, "fstat");

    // Check if working with REGULAR file, mmap doesn't work if not
    if(!S_ISREG(stat_buf.st_mode)) {
        printf("\033[31;1m file is not supported!\033[0m\n");
        exit(1);
    }

    // Make the mapping
    map_data = mmap(NULL, stat_buf.st_size, PROT_READ, MAP_SHARED, fd, 0); // NULL because we don't care about address, SHARED o PRIVATE in this case would be the same
    check_map_err((void *)map_data, "mmap");

    // We can close the file once mapped
    close(fd);

    // Starting from the address of the mapping we can start to read each byte
    for(int i=0; i<stat_buf.st_size; i++) 
        putchar(map_data[i]);

    retcode = munmap((void*)map_data, stat_buf.st_size);
    check_err(retcode, "munmap");
}