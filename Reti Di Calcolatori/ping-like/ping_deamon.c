#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <arpa/inet.h>

#define MAXBUF 32

void check_error(int retcode, char* message) {
    if (retcode == -1) {
        printf("%s\n", message);
        exit(-1);
    }
}

int main(int argc, char** argv) {
    int sockfd, retcode;
    struct sockaddr_in local_addr, remote_addr;
    socklen_t len = sizeof(local_addr);
    char buffer[MAXBUF];

    if (argc != 2) {
        printf("Usage: %s listening_PORT\n", argv[0]);
        return -1;
    }

    sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    check_error(sockfd, "Error on opening socket..");

    memset(&local_addr, 0, len);
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(atoi(argv[1]));

    retcode = bind(sockfd, (struct sockaddr *) &local_addr, len);
    check_error(retcode, "Error on binding socket..");

    while (1) {
        recvfrom(sockfd, buffer, MAXBUF-1, 0, (struct sockaddr *) &remote_addr, &len);
        printf("From IP: %s Port: %d\n", inet_ntoa(remote_addr.sin_addr), ntohs(remote_addr.sin_port));
        sendto(sockfd, buffer, MAXBUF-1, 0, (struct sockaddr *) &remote_addr, len);
    }
}