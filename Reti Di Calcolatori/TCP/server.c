#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define MAXBUF 1024
#define MAXCONC 5

void check_error(int retcode, char* message) {
    if (retcode == -1) {
        printf("%s\n", message);
        return -1;
    }
}

int main(int argc, char** argv) {
    int sockA, sockB, retcode;
    struct sockaddr_in local_addr, remote_addr;
    socklen_t len = sizeof(local_addr);
    char buffer[MAXBUF];

    if (argc != 2) {
        printf("Usage: %s listening_PORT\n", argv[0]);
        return -1;
    }

    sockA = socket(PF_INET, SOCK_STREAM, 0);
    check_error(sockA, "Error on opening socket...");

    memset(&local_addr, 0, len);
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(atoi(argv[1]));

    retcode = bind(sockA, (struct sockaddr *) &local_addr, len);
    check_error(retcode, "Error on binding socket...");

    listen(sockA, MAXCONC);

    while (1) {
        sockB = accept(sockA, (struct sockaddr *) &remote_addr, &len);

        if (fork() == 0) {
            close(sockA);

            while (1) {
                retcode = recv(sockB, buffer, MAXBUF-1, 0);
                check_error(retcode, "Error on receiving package..");
                
                buffer[retcode] = 0;
                send(sockB, buffer, retcode, 0);
            }
        }
        else 
            close(sockB);
    }
}