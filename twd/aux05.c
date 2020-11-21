#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define SERVERIP "90.147.166.230"
#define SERVERPORT 8080
#define REQUEST "GET /prova/05.aux\r\n"

char buffer[1024];

int main(int argc, char* argv[]) {
    int sock_fd;
    struct sockaddr_in server_addr;
    int retcode;

    // Create client socket
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd == -1) {
        perror("Error creating socket...\n");
        return -1;
    }

    // Set server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVERPORT);
    inet_aton(SERVERIP, &server_addr.sin_addr);

    // Connect socket to server
    retcode = connect(sock_fd, (struct sockaddr*) &server_addr, sizeof(server_addr));
    if(retcode == -1) {
        perror("Error connecting to socket..\n");
        return -1;
    }

    printf("Connected to server@%s", SERVERIP);

    // Send request to server
    retcode = send(sock_fd, &REQUEST, sizeof(REQUEST), 0);
    if(retcode == -1) {
        perror("Error sending message to server..\n");
        return -1;
    }

    char c;
    char s[1024];
    int index = -1;
    int flag = 0;

    while((retcode = recv(sock_fd, &c, 1, 0) ) > 0) {
        if(c == '['){
            flag = 1;
        }
        else if(c == ']'){
            flag = 0;
            s[++index] = '\r';
            s[++index] = '\n';
        }

        if(flag == 1) {
            s[++index] = c;
        }
    }

    close(sock_fd);
    printf("\nClosed connection with server.");

    memcpy(&s, &s[1], sizeof(s) -1);
    printf("\nResult: %s", s);

    // Create new socket
    int newsock_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    // Connect to server
    retcode = connect(newsock_fd, (struct sockaddr*) &server_addr, sizeof(server_addr));
    if(retcode == -1) {
        perror("Error connecting to server..\n");
        return -1;
    }

    retcode = send(sock_fd, &s, sizeof(s), 0);
    if(retcode == -1) {
        perror("Error sending to server..\n");
        return -1;
    }

    memset(&buffer, 0, sizeof(buffer));
    retcode = recv(sock_fd, &buffer, sizeof(buffer), 0);
    if(retcode == -1) {
        perror("Error recving..\n");
        return -1;
    }

    printf("\nResult: %s\n", buffer);

}