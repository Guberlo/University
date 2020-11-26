/*
    Scrivere un server che si metta in ascolto sul port 3333 in grado di rispondere ad un messaggio composto da una sola stringa str composta da cifre numeriche (da 0 a 9) terminata dal carattere \n.

    Il server:
    Converte la stringa ricevuta str in un numero intero n.
    Il numero viene usato come input per il metodo “int cubo(int n)” che restituisce il cubo dell’intero n.
    Il server invia al client il valore restituito dal metodo cubo(). 

    Testare il server con un semplice client o con telnet.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <math.h>

#define SERVERIP "127.0.0.1"
#define SERVERPORT 3333
#define MAXQUEUE 1
#define MAXLEN 1024

char buffer[MAXLEN];

void check_err(int value, char* msg) {
    if(value == -1) {
        perror(msg);
        exit(-1);
    }
}

int cubo(int n) {
    return pow(n, 3);
}

int main(int argc, char** argv) {
    setbuf(stdout, NULL);
    int server_socket, connection_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len;
    int retcode;

    // Create server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    check_err(server_socket, "socket creation");

    // Reuse address
    int reuse = 1;
    retcode = setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    check_err(retcode, "reuse");

    // Make server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVERPORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind address to socket
    retcode = bind(server_socket, (struct sockaddr*) &server_addr, sizeof(server_addr));
    check_err(retcode, "bind");

    // Listen for connections
    listen(server_socket, MAXQUEUE);

    // Accept requests
    client_addr_len = sizeof(client_addr);


    while(1) {
        connection_socket = accept(server_socket, (struct sockaddr*) &client_addr, &client_addr_len);
        check_err(connection_socket, "accept");

        // Read data
        retcode = recv(connection_socket, &buffer, MAXLEN - 1, 0);
        check_err(retcode, "recv");

        if(retcode == 0) {
            printf("\nClosing connection with client.");
            close(connection_socket);
        }

        buffer[retcode] = '\0';

        printf("\nBuffer: %s", buffer);

        int x = atoi(buffer);

        printf("\nConverted to: %d", x);

        int response = cubo(x);

        printf("\nCubo: %d", response);
        
        // Converting response to string
        int length = snprintf(NULL, 0, "%d" , response);
        printf("\nLength: %d", length);
        char* res = malloc(length + 1);
        sprintf(res, "%d", response);

        // print converted value
        printf("\nConverted to string: %s", res);

        // Send response to client
        retcode = send(connection_socket, res, sizeof(res), 0);
        check_err(retcode, "send");
        printf("\nSent response to client");

        free(res);

        close(connection_socket);
        printf("\nClosed connection with client.\n");

    }
}