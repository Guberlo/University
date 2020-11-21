#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define SERVERIP "90.147.166.230"
#define SERVERPORT 8080
#define REQUEST "GET /prova/06.aux\r\n"

char c;
char buffer[1024];

int main(int argc, char* argv[]) {
    setbuf(stdout, NULL);
    int sock_fd;
    struct sockaddr_in server_addr;
    int retcode;

    // Create client socket
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd == -1) {
        perror("\nError creating socket..");
        return -1;
    }

    // Make server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVERPORT);
    inet_aton(SERVERIP, &server_addr.sin_addr);

    // Connect socket to server
    retcode = connect(sock_fd, (struct sockaddr*) &server_addr, sizeof(server_addr));
    if(retcode == -1) {
        perror("\nError connecting to server..");
        return -1;
    }

    printf("\nConnected to server@%s", SERVERIP);

    // Send request to server
    retcode = send(sock_fd, &REQUEST, sizeof(REQUEST), 0);
    if(retcode == -1) {
        perror("\nError sending to server..");
        return -1;
    }
    
    int flag, index = 0;
    char s[1024];

    memset(&s, 0, sizeof(s));
    // Taking all the char starting from the first not equal to 'x'
    while(recv(sock_fd, &c, 1, 0) > 0) {
        if(c != 'x' && c != '\n' && c != ' ') {
            flag = 1;
        }

        if(flag == 1 && c != '\n') {
            printf("%c", c);
            s[index++] = c;
        }
    }

    close(sock_fd);

    s[index++] = '\r';
    s[index++] = '\n';
    
    printf("\nOpening a new connection: %d", index);

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd == -1) {
        perror("\nError creating socket..");
        return -1;
    }

    // Open a new connection
    retcode = connect(sock_fd, (struct sockaddr*) &server_addr, sizeof(server_addr));
    if(retcode == -1) {
        perror("\nError connecting to server..");
        return -1;
    }

    printf("\nConnected again to server@%s", SERVERIP);

    printf("\nRequest: '%s', size: %lu \n", s, sizeof(s));

    // Send request to server
    retcode = send(sock_fd, &s, sizeof(s), 0);
    if(retcode == -1) {
        perror("\nError sending to server..");
        return -1;
    }

    memset(&buffer, 0, sizeof(buffer));
    // Get response
    if( (retcode = recv(sock_fd, &buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[retcode] = '\0';
    }

    close(sock_fd);

    printf("\nResponse: %s", buffer);

    return 0;
}