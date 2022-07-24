#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define SRV_ADDR "10.0.0.1"
#define SRV_PORT 42389
#define LST_PORT 48782
#define BUFSIZE 1024

void check_err(int retcode, char* message) {
    if (retcode < 0) {
        printf("%s\n", message);
        exit(-1);
    }
}

int main(int argc, char** argv) {
    int retcode, sockfd, max = 5;
    struct sockaddr_in srv_addr;
    socklen_t len = sizeof(srv_addr);
    char buffer[BUFSIZE];
    char restart[2];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    check_err(sockfd, "error on opening socket");

    memset(&srv_addr, 0, len);
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(SRV_PORT);
    srv_addr.sin_addr.s_addr = inet_addr(SRV_ADDR);

    retcode = sendto(sockfd, "1", sizeof("1"), 0, (struct sockaddr*) &srv_addr, len);
    check_err(retcode, "error on sending message");

    retcode = recvfrom(sockfd, buffer, BUFSIZE-1, 0, (struct sockaddr*) &srv_addr, &len);
    check_err(retcode, "error on receiving message");
    buffer[retcode] = '\0';

    printf("Data and time retrieved: %s\n", buffer);

    while (1) {

        for (int i=0; i<max; i++) {
            retcode = recvfrom(sockfd, buffer, BUFSIZE-1, 0, (struct sockaddr*) &srv_addr, &len);
            check_err(retcode, "error on receiving message");
            buffer[retcode] = '\0';
            printf("Data and time retrieved: %s\n", buffer);
        }

        printf("Do you wish to continue communication? [y/n]\n");
        scanf("%s", restart);

        if (restart[0] != 'y') {
            retcode = sendto(sockfd, "n", sizeof("n"), 0, (struct sockaddr*) &srv_addr, len);
            check_err(retcode, "error on sending message");
            exit(-1);
        }

        retcode = sendto(sockfd, "1", sizeof("1"), 0, (struct sockaddr*) &srv_addr, len);
        check_err(retcode, "error on sending message"); 

        max = 6; 
    }
}