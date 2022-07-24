/**
 * https://drive.google.com/drive/u/0/folders/1NLVXpHEf6reBe5hv464NPPYzfLEB34gH
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>

#define LST_PORT 42389

void check_err(int retcode, char* message) {
    if (retcode < 0) {
        printf("%s\n", message);
        exit(-1);
    }
}

int main(int argc, char** argv) {
    int retcode, sockfd;
    struct sockaddr_in local_addr, client_addr;
    socklen_t len = sizeof local_addr;
    char c[2];
    char buffer[1024];
    time_t now;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    check_err(sockfd, "error on creating socket");

    memset(&local_addr, 0, len);
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(LST_PORT);

    retcode = bind(sockfd, (struct sockaddr*) &local_addr, len);
    check_err(retcode, "error on binding to socket");

    while (1) {
        retcode = recvfrom(sockfd, c, sizeof(c), 0, (struct sockaddr*) &client_addr, &len);
        check_err(retcode, "error on receiving");
        if (!fork()) {
            c[0] = 'y';

            while (c[0] == 'y') {
                // send date to client every 5 seconds 6 times
                for (int i=0; i<6; i++) {
                    time(&now);
                    sprintf(buffer, "%s", ctime(&now));
                    retcode = sendto(sockfd, buffer, 1024, 0, (struct sockaddr*) &client_addr, len);
                    check_err(retcode, "error on resending date");
                    sleep(5);
                }
                // check if the client wants to communicate again or not
                retcode = recvfrom(sockfd, c, sizeof(c), 0, (struct sockaddr*) &client_addr, &len);
                check_err(retcode, "error on receiving again");

                if (c[0] != 'y')
                    exit(0);
            }   
        }
    }
}