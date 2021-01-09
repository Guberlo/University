#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

void check_err(int value, char* msg) {
    if(value == -1) {
        perror(msg);
        exit(1);
    }
}

void check_map_err(void* value, char* msg) {
    if(value == MAP_FAILED) {
        perror(msg);
        exit(1);
    }
}

int main(int argc, char** argv) {
    int sd, dd; // Source and destination descriptors;
    int retcode;
    struct stat stat_buff;
    char* src_data, *dest_data;

    if(argc != 3) {
        printf("\033[31;1m use: mmapcopy path/file2.txt directory-destinazione\033[0m\n");
    }

    // Open source file
    sd = open(argv[1], O_RDONLY);
    check_err(sd, "open1");

    // File's stats
    retcode = fstat(sd, &stat_buff);
    check_err(retcode, "fstat");

    // Open destination file
    dd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, stat_buff.st_mode & 0777);
    check_err(dd, "open2");

    // If we are mapping an empty file we are done
    if(stat_buff.st_size == 0)
        exit(0);

    // If not, we need to make the destination file as big as the source in order to map it
    retcode = ftruncate(dd, stat_buff.st_size);
    check_err(retcode, "truncate");

    // Map the source file
    src_data = mmap(NULL, stat_buff.st_size, PROT_READ, MAP_SHARED, sd, 0);
    check_map_err((void*)src_data, "mmap s");

    // Map the destination file
    dest_data = mmap(NULL, stat_buff.st_size, PROT_WRITE, MAP_SHARED, dd, 0);
    check_map_err((void*)dest_data, "mmap d");

    for(int i=0; i<stat_buff.st_size; i++)
        dest_data[i] = src_data[i];
    
    printf("\033[33;1m mapped succesfully:\n %s\n", dest_data);

    munmap(src_data, stat_buff.st_size);
    munmap(dest_data, stat_buff.st_size);
    close(sd);
    close(dd);
}