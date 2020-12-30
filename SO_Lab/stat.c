/**
 * Show file stats using stat()
 * 1. filename
 * 2. permissions
 * 3. type
 * 4. i-node number
 * 5. Username e Groupname
 * 6. atime
 * 7. mtime
 * 8. ctime
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>

#define MAXLEN 1024

int check_err(int code, char* msg) {
    if(code == -1) {
        perror(msg);
        exit(1);
    }

    return 0;
}

int main(int argc, char** argv) {
    int retcode;
    const char* type;
    struct passwd* pw;
    struct group* gr;
    const char* username, *groupname;
    struct stat buffer;

    if(argc != 2) {
        printf("\033[31m utilizzo: stat <file path> \033[0m\n");
        exit(1);
    }

    // Save file stats to buffer
    retcode = lstat(argv[1], &buffer);
    check_err(retcode, "lstat");

    // Get type of file
    if(S_ISBLK(buffer.st_mode) || S_ISCHR(buffer.st_mode))
        type = "special file";
    else if(S_ISDIR(buffer.st_mode))
        type = "directory";
    else if(S_ISFIFO(buffer.st_mode))
        type = "FIFO file";
    else if(S_ISREG(buffer.st_mode))
        type = "regular file";
    else if(S_ISLNK(buffer.st_mode))
        type = "link file";
    else 
        type = "<----file not supported---->";

    // Username
    pw = getpwuid(buffer.st_uid);
    if(pw)
        username = pw->pw_name;
    else 
        username = "?????";

    // Groupname
    gr = getgrgid(buffer.st_gid);
    if(gr)
        groupname = gr->gr_name;
    else 
        groupname = "?????";


    printf("# \033[35;1m pathname: %s \033[0m\n", argv[1]); // filename
    printf("# \033[35;1m permissions: %o \033[0m\n", buffer.st_mode & 0777); // permission
    printf("# \033[35;1m type: %s \033[0m\n", type);
    printf("# \033[35;1m i-number: %d \033[0m\n", buffer.st_ino);
    printf("# \033[35;1m username: %s \033[0m\n", username);
    printf("# \033[35;1m groupname: %s \033[0m\n",groupname);
    printf("# \033[33;1m c_time: %s \033[0m", asctime(localtime(&(buffer.st_ctime))));
    printf("# \033[33;1m a_time: %s \033[0m", asctime(localtime(&(buffer.st_atime))));
    printf("# \033[33;1m m_time: %s \033[0m", asctime(localtime(&(buffer.st_mtime))));

}