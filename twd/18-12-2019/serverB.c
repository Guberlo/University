#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>

#define SERVERIP "127.0.0.1"
#define SERVERPORT 7777
#define MAXQUEUE  1
#define MAXLEN 1024

char buffer[MAXLEN];

void check_err(int value, char* mesg) {
    if(value == -1) {
        perror(mesg);
        exit(-1);
    }
}

int MUL (char* );

int main(int argc, char** argv) {
    int server_socket, connection_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len;
    int retcode;

    // Create server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    check_err(server_socket, "socket creation");

    // Make server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVERPORT);
    inet_aton(SERVERIP, &server_addr.sin_addr);

    // Bind address to socket
    retcode = bind(server_socket, (struct sockaddr*) &server_addr, sizeof(server_addr));
    check_err(retcode, "bind");

    // Listen for connections
    retcode = listen(server_socket, MAXQUEUE);

    // Accept connections
    client_addr_len = sizeof(client_addr);

    while(1) {
        connection_socket = accept(server_socket, (struct sockaddr*) &client_addr, &client_addr_len);

        // Read data
        retcode = recv(connection_socket, &buffer, MAXLEN - 1, 0);
        check_err(retcode, "recv");

        if( retcode == 0) {
            printf("\nClosing connection.");
            close(connection_socket);
        }
        else {
            buffer[retcode] = '\0';

            int response = MUL(buffer);

            printf("\nNew message from client: %s", response);

            send(connection_socket, response, MAXLEN, 0);

            close(connection_socket);
        }

    }
    
    
}

int MUL(char* msg) {
    return 0;
}