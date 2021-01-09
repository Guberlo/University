/*
    Homework n.4

    Estendere l'esercizio 'homework n.1' affinche' operi correttamente
    anche nel caso in cui tra le sorgenti e' indicata una directory, copiandone
    il contenuto ricorsivamente. Eventuali link simbolici incontrati dovranno
    essere replicati come tali (dovrà essere creato un link e si dovranno
    preservare tutti permessi di accesso originali dei file e directory).

    Una ipotetica invocazione potrebbe essere la seguente:
     $ homework-4 directory-di-esempio file-semplice.txt path/altra-dir/ "nome con spazi.pdf" directory-destinazione
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <libgen.h>

#define MAXLEN 2048

void check_err(int value, char *msg)
{
    if (value == -1)
    {
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

void copy(char *from, char *to)
{
    struct stat stat_buf;
    int fd; // File descriptor
    int dd; // Destination file descriptor
    int read_code, write_code;
    char buffer[MAXLEN];
    char destination[MAXLEN];
    int retcode;

    printf("\033[33;1mCopying from: %s to %s\033[0m\n", from, to);

    memset(&stat_buf, 0, sizeof(stat_buf));
    memset(&buffer, 0, MAXLEN);
    memset(&destination, 0, MAXLEN);

    retcode = lstat(from, &stat_buf);
    check_err(retcode, "lstat");

    if (S_ISREG(stat_buf.st_mode))
    {
        printf("\033[32;1mCopying regular file\033[0m\n");
        char *path;

        path = strdup(from);
        path = __xpg_basename(path);

        printf("\033[35;1mPath: %s\033[0m\n", path);

        fd = open(from, O_RDONLY);
        check_err(fd, "open");

        strcpy(destination, to);
        strcat(destination, path);

        printf("\033[35;1mdestination: %s\033[0m\n", destination);

        dd = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0660);
        check_err(dd, "open destination");

        do
        {
            read_code = read(fd, buffer, sizeof(buffer));
            check_err(read_code, "read");

            write_code = write(dd, buffer, read_code);
            check_err(write_code, "write");
        } while (read_code > 0);

        close(dd);
        close(fd);
    }
    else if (S_ISDIR(stat_buf.st_mode))
    {
        char* dirname = strdup(from); 
        strcpy(dirname, basename(dirname));

        char* new_dir = strdup(to);
        strcat(new_dir, dirname);
        strcat(new_dir, "/");

        printf("\033[35;1mdirname: %s\033[0m\n", new_dir);

        retcode = mkdir(new_dir, stat_buf.st_mode & 0777);
        check_err(retcode, "mkdir");
        
        DIR *dir_stream = opendir(from);
        check_dir_err(dir_stream);

        struct dirent* dir;
        while( (dir = readdir(dir_stream)) != NULL) {
            if(strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
                continue;
            char path[MAXLEN];
            strcpy(path, from);
            strcat(path, dir->d_name);
            copy(path, new_dir);
        }

        closedir(dir_stream);
    }
    else if (S_ISLNK(stat_buf.st_mode))
    {
        printf("\033[33;1m Copying symlink: from %s, to %s\033[0m\n", from, to);

        retcode = readlink(from, buffer, MAXLEN - 1);
        check_err(retcode, "readlink");
        buffer[retcode] = '\0';

        char* path = strdup(from);
        path = basename(path);

        strcpy(destination, to);
        strcat(destination, path);

        printf("\033[35;1mdestination: %s\033[0m\n", destination);
        printf("\033[35;1mbuffer: %s\033[0m\n", buffer);

        retcode = symlink(buffer, destination);
        check_err(retcode, "symlink");
    }
    else 
        printf("\033[33;1mFile not supported\033[0m\n");
}

int main(int argc, char **argv)
{
    struct stat stat_buf;
    int fd; // File descriptor
    int dd; // Destination file descriptor
    int read_code, write_code;
    char buffer[MAXLEN];
    char destination[MAXLEN];
    int retcode;

    if (argc < 3)
    {
        printf("\033[31;1m use: homework-4 file1.txt path/file2.txt \"nome con spazi.pdf\" directory-destinazione\033[0m\n");
        exit(1);
    }

    for (int i = 1; i < argc - 1; i++)
    {
        copy(argv[i], argv[argc - 1]);
    }

    printf("\033[33;1m Copied succesfully!\033[0m\n");
}