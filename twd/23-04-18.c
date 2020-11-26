#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>

#define SERVERPORT 3333
#define MAXQUEUE 1
#define MAXLEN 1024

char buffer[MAXLEN];

void check_err(int value, char* msg) {
    if(value == -1 ){
        perror(msg);
        exit(-1);
    }
}

int sommacifre(char* request) {
    printf("\n%s", request);
    int length = strlen(request);
    printf("\nLength: %d", length);
    int sum = 0;

    for(int i=0; i<length; i++) {
        if(request[i] >= '0' && request[i] <= '9') {
            int x = request[i] - '0';
            printf("\n%c, %d", request[i], x);
            sum = sum + x;
        }
    }
    return sum;
}

int main(int argc, char** argv) {
    setbuf(stdout, NULL);
    int server_socket, connection_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len;
    int retcode;
    int n = 0;

    // Create server_socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    check_err(server_socket, "socket creation");

    int reuse = 1;
    retcode = setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    // Make server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVERPORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind address to socket
    retcode = bind(server_socket, (struct sockaddr*) &server_addr, sizeof(server_addr));
    check_err(retcode, "bind");

    // Listen for requests
    listen(server_socket, MAXQUEUE);

    // Accept connections
    client_addr_len = sizeof(client_addr);

    while(1) {
        connection_socket = accept(server_socket, (struct sockaddr*) &client_addr, &client_addr_len);

        // Read data from socket
        retcode = recv(connection_socket, &buffer, MAXLEN - 1, 0);
        check_err(retcode, "recv");

        if(retcode == 0) {
            printf("Closing connection with client.");
            close(connection_socket);
        }

        n++;
        buffer[retcode] = '\0';

        int somma = sommacifre(buffer);

        int n_len = snprintf(NULL, 0, "%d", n);
        int somma_len = snprintf(NULL, 0, "%d", somma);
        int array_len = n_len + somma_len + 2;
        char message[array_len];
        sprintf(message, "%d, %d", n, somma);

        printf("\nRequest: %s", message);
        printf("\nSize: %lu, %d", sizeof(message), array_len);

        send(connection_socket, message, array_len, 0);

        close(connection_socket);
    }
}