#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVERNAME "90.147.166.230"
#define SERVERPORT 8080
#define REQUEST "GET /pappalardo/prova/04.aux\r\n"
#define MIN 397568
#define MAX 397613

int main(int argc, char* argv[]) {
    int sock_fd;
    int retcode;
    struct sockaddr_in server_addr;

    // Set server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVERPORT);
    inet_aton(SERVERNAME, &server_addr.sin_addr);

    // Create client socket
    if( (sock_fd=socket(AF_INET, SOCK_STREAM, 0)) == -1 ) {
        perror("Error creating socket...");
        exit(1);
    }

    // Connect to server
    if( (connect(sock_fd, (struct sockaddr *) &server_addr, sizeof(server_addr))) == -1) {
        perror("Error while connecting to socket...");
        exit(1);
    }

    // Send request to server
    if( (send(sock_fd, REQUEST, sizeof(REQUEST), 0)) == -1) {
        perror("Error sending to server...");
        exit(1);
    }

    // Reading every character until the start of our interest MIN
    char character;
    int index = -1;

    while(index < MIN) {
        retcode = recv(sock_fd, &character, 1, 0);
        if(retcode == -1) {
            perror("Error in recv...");
            exit(1);
        }
        else if(retcode == 0) {
            printf("Closing connection...");
            exit(0);
        }

        index += retcode;
    }

    printf("%c", character);

    // Read all the characters between MIN and MAX
    while (index < MAX) {
        retcode = recv(sock_fd, &character, 1, 0);
        if(retcode == -1) {
            perror("Error in recv...");
            exit(1);
        }
        else if(retcode == 0) {
            printf("Closing connection...");
            exit(0);
        }

        index += retcode;
        printf("%c", character);
    }

    printf("\n");
    close(sock_fd);

    return 0;
}
