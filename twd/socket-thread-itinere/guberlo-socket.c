/*
    Scrivere un server che si metta in ascolto sul port 7777 in grado di rispondere ad un messaggio composto da una stringa .

    Il server dovrà inviare al cliente la stringa più lunga che abbia ricevuto
    durante la sua esecuzione. 

    Testare il server con un semplice client o con telnet.
*/

#include <asm-generic/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define SERVERPORT 7777
#define MAXQUEUE 1
#define MAXLEN 1024

char buffer[MAXLEN];

void check_err(int value, char* msg) {
    if(value == -1) {
        perror(msg);
        exit(-1);
    }
}

int main(int argc, char** argv) {
    setbuf(stdout, NULL);
    int server_socket, connection_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len;
    int retcode;
    char msg[MAXLEN];
    char tmp[MAXLEN];
    int maxlen = 0;

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    check_err(server_socket, "socket creation");
    int reuse = 1;
    retcode = setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    check_err(retcode, "reuse");

    // Make addr server
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVERPORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind addr to socket
    retcode = bind(server_socket, (struct sockaddr*) &server_addr, sizeof(server_addr));
    check_err(retcode, "bind");

    // Listen for connections
    listen(server_socket, MAXQUEUE);

    // Accept connections
    client_addr_len = sizeof(client_addr);

    while(1) {
        connection_socket = accept(server_socket, (struct sockaddr*) &client_addr, &client_addr_len);

        // Read 
        retcode = recv(connection_socket, &buffer, MAXLEN - 1, 0);
        check_err(retcode, "recv");

        if(retcode == 0) {
            printf("\nClosing connection with client.");
            close(connection_socket);
        }

        buffer[retcode] = '\0';
        
        // Clear msg to do a correct comparison
        memset(msg, 0, MAXLEN);

        printf("\nBuffer: '%s'", buffer);
        printf("\nlength of buff: %lu", strlen(buffer));
        printf("\nlength of msg before: %lu", strlen(msg));

        // If the length of the buffer is greater than the max length
        if(strlen(buffer) > strlen(msg) && strlen(buffer) > maxlen) {
            printf("\nBuffer maggiore!");
            strcpy(msg, buffer); 
            printf("\nmsg: '%s'", msg);
            printf("\nlength of msg: %lu\n", strlen(msg));
            memset(tmp, 0, MAXLEN);
            strcpy(tmp, msg);
            printf("\ntmp: '%s'", tmp);
            printf("\nlength of tmp: %lu\n", strlen(tmp));
            maxlen = strlen(buffer);
        }

        printf("\nmaxlen: %d", maxlen);

        printf("\ntmp: '%s'", tmp);
        send(connection_socket, &tmp, MAXLEN, 0);

        close(connection_socket);
    }

}