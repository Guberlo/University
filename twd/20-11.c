/*
    Esercizio prova in itinere:
    Ricevere una stringa e sostituire tutti i suoi caratteri
    con delle x e inviare la risposta nuovamente al cliente.
*/

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>

#define SERVERIP "127.0.0.1"
#define SERVERPORT 7777
#define DIM 1024

char buffer[DIM];

void check_error(int value, char* message) {
    if(value == -1) {
        perror(message);
        exit(-1);
    }
}

int main(int argc, char** argv) {
    int server_socket, connection_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len;
    int retcode;

    // Create server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    check_error(server_socket, "socket creation");

    // Make server addr
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVERPORT);
    inet_aton(SERVERIP, &server_addr.sin_addr);

    // Bind address to socket

    retcode = bind(server_socket, (struct sockaddr*) &server_addr, sizeof(server_addr));
    check_error(retcode, "bind");

    // Listen for request
    listen(server_socket, 1);

    // Accept request
    client_addr_len = sizeof(client_addr);

    while(1) {
        connection_socket = accept(server_socket, (struct sockaddr*) &client_addr, &client_addr_len);
        check_error(connection_socket, "accept");

        // Recv data and close connection
        retcode = recv(connection_socket, &buffer, DIM - 1, 0);

        check_error(retcode, "recv");

        if(retcode > 0) {
            buffer[retcode] = '\0';

            for(int i=0; i<retcode-2; i=i+2) {
                buffer[i] = 'X';
            }

            send(connection_socket, &buffer, DIM, 0);
        }

    }

/*
        // Read data and keep listen
        while( (retcode = recv(connection_socket, &buffer, DIM-1, 0)) > 0) {
            buffer[retcode] = '\0';

            for(int i=0; i<retcode-2; i=i+2) {
                buffer[i] = 'X';
            }

            send(connection_socket, &buffer, DIM, 0);
        }

        check_error(retcode, "recv");

        if(retcode == 0) {
            close(connection_socket);
            break;
        }

*/
}