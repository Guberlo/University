#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>

#define SERVERIP "127.0.0.1"
#define SERVERPORT 3333
#define MAXLEN 1024

char buffer[MAXLEN];

void check_err(int value, char* msg){
    if(value == -1) {
        perror(msg);
        exit(-1);
    }
}

int main(int argc, char** argv) {
    setbuf(stdout, NULL);
    int sock_fd;
    struct sockaddr_in server_addr;
    socklen_t server_addr_len = sizeof(server_addr);
    int retcode;

    // Create socket
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    check_err(sock_fd, "socket creation");

    // Make server addr
    memset(&server_addr, 0, server_addr_len);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVERPORT);
    inet_aton(SERVERIP, &server_addr.sin_addr);

    // Connect to server

    retcode = connect(sock_fd, (struct sockaddr*) &server_addr, server_addr_len);
    check_err(retcode, "connect");

    printf("\nConnected to server@%s", SERVERIP);
    printf("\nInsert a number: ");

    int x;
    scanf("%d", &x);

    // Send data to server

    int length = snprintf(NULL, 0, "%d", x);
    char* request = malloc(length + 1);
    sprintf(request, "%d", x);

    send(sock_fd, request, sizeof(request), 0);

    free(request);

    // Read data from server
    retcode = recv(sock_fd, &buffer, MAXLEN - 1, 0);
    check_err(retcode, "recv");

    if(retcode == 0) {
        printf("\nClosing connection with server.");
        close(sock_fd);
    }

    buffer[retcode] = '\0';
    printf("\nResponse: %s", buffer);

    close(sock_fd);
}