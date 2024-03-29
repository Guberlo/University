/*


*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#define SERVERIP "127.0.0.1"
#define SERVERPORT 7777
#define MAXQUEUE 1
#define MAXLEN 1024

char buffer[MAXLEN];

void check_err(int value, char* mesg) {
    if(value == -1) {
        perror(mesg);
        exit(-1);
    }
}

int MUL(char* mesg) {
    int res = 1;
    int lenght = sizeof(mesg)/sizeof(char);
    printf("MESSAGIO: %s", mesg);
    printf("LENGHT: %d", lenght);

    for(int i=0; i<lenght-2; i++) {
        if(mesg[i] >= '0' && mesg[i] <= '9') {
            int c = mesg[i] - '0';
            printf("\nC = %c, %d", mesg[i], c);
            res = res * c;
        }
    }

    return res;
}

int main(int argc, char** argv) {
    setbuf(stdout, NULL);
    int server_socket, connection_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len;
    int retcode;

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    check_err(server_socket, "socket creation");

    // Reuse socket
    int reuse = 1;
    retcode = setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    check_err(retcode, "reuse");

    // Make server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVERPORT);
    inet_aton(SERVERIP, &server_addr.sin_addr);

    // Bind address to socket
    retcode = bind(server_socket, (struct sockaddr*) &server_addr, sizeof(server_addr));
    check_err(retcode, "Bind");

    // Listen for requests
    listen(server_socket, MAXQUEUE);

    // Accept requests
    client_addr_len = sizeof(client_addr);

    while (1) {
        connection_socket = accept(server_socket, (struct sockaddr*) &client_addr, &client_addr_len);
        check_err(connection_socket, "accept");

        // Read data from socket
        retcode = recv(connection_socket, &buffer, MAXLEN - 1, 0);
        check_err(retcode, "recv");
        if(retcode == 0) {
            printf("\nClosing connection with server.");
            close(connection_socket);
        }
        else {
            buffer[retcode] = '\0';

            int response = MUL(buffer);
            printf("\nResponse: %d", response);
            char mesg[10];

            sprintf(mesg, "%d", response);

            printf("\nMesg = %s", mesg);
            
            int len = sizeof(mesg)/sizeof(mesg[0]);

            mesg[len] = '\0';

            send(connection_socket, &mesg, sizeof(mesg), 0);

            close(connection_socket);
        }
    }
}