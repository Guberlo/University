/**
 * File creator
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char** argv) {
    int fd; // File Descriptor
    char filename[256];
    printf("<--File creator-->\n");
    printf("Insert a file name with an extension:");
    scanf("%s", filename);
    printf("%s\n", filename);
    fd = creat(filename, 0666); // 0666 is the octal of 666 (-rw-r-r)
    if( fd == -1) {
        perror("Creat");
        exit(1);
    }

    printf("File %s succesfully created.\n", filename);
}