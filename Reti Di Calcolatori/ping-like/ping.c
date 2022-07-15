#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>

#define MAXBUF 32

void check_error(int retcode, char* message) {
    if (retcode == -1) {
        printf("%s\n", message);
        exit(-1);
    }
}

int main(int argc, char** argv) {
    int sockfd, retcode;
    struct sockaddr_in remote_addr;
    socklen_t len = sizeof(remote_addr);
    struct timespec start;
    char buffer[MAXBUF];

    if (argc != 3) {
        printf("Usage: %s destination_IP destination_PORT\n", argv[0]);
        return -1;
    }

    sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    check_error(sockfd, "Error on opening socket..");

    if (!fork()) {
        struct timespec send_time, current_time;
        int count;
        long sec, nsec;

        while(1) {
            recvfrom(sockfd, buffer, MAXBUF-1, 0, (struct sockaddr *) &remote_addr, &len);
            clock_gettime(CLOCK_REALTIME, &current_time); 
            memcpy(&count, buffer, sizeof(count));
            memcpy(&send_time, buffer + sizeof(count), sizeof(send_time));

            sec = current_time.tv_sec - send_time.tv_sec;
            nsec = current_time.tv_nsec - send_time.tv_nsec;

            printf("Ping from:%s Port:%d Ping:%d Time: sec=%ld nsec=%ld\n", inet_ntoa(remote_addr.sin_addr), ntohs(remote_addr.sin_port), count, sec, nsec);
        }
    }
    else {
        memset(&remote_addr, 0, len);
        remote_addr.sin_family = AF_INET;
        remote_addr.sin_port = htons(atoi(argv[2]));
        inet_pton(AF_INET, argv[1], &(remote_addr.sin_addr));
    
        // Send 10 packets
        for (int i=0; i<10; i++) {
            clock_gettime(CLOCK_REALTIME, &start);
            memcpy(buffer, &i, sizeof(i));
            memcpy(buffer+sizeof(i), &start, sizeof(start));
            sendto(sockfd, buffer, MAXBUF-1, 0, (struct sockaddr *) &remote_addr, len);
            sleep(1);
            printf("Sending ping number %d\n", i);
        }
    }
}
