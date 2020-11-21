#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>

#define SERVERIP "90.147.166.230"
#define SERVERPORT 8080
#define REQUEST "GET /prova/04.aux\r\n\r\n"
#define START 397567
#define END 397613

char buffer[1024];

int main(int argc, char* argv[]) {
    setbuf(stdout, NULL);
    int sock_fd;
    struct sockaddr_in server_addr;
    int retcode;

    // Creating client socket
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd == -1) {
        perror("Error creating socket..");
        return -1;
    }

    // Prepare server addres to connect
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_port = htons(SERVERPORT);
    server_addr.sin_family = AF_INET;
    inet_aton(SERVERIP, &server_addr.sin_addr);

    // Connect socket to server
    retcode = connect(sock_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));
    if(retcode == -1) {
        perror("Error connecting to server socket...");
        return -1;
    }

    printf("Connected to server@%s", SERVERIP);

    // Send request to server
    retcode = send(sock_fd, REQUEST, sizeof(REQUEST), 0);
    if(retcode == -1) {
        perror("Error sending data..");
        return -1;
    }

    printf("\nRequest sent to server. Waiting for response...\n");

        // Read data from server
    char c;
    int index = -1;

    // Read the first 397568 bytes
    while(index++ < START) {
        retcode = recv(sock_fd, &c, 1, 0); // Reading char by char
        if(retcode == -1) {
            perror("Error reading from server");
            return -1;
        }
    }

    // Read from START to END
    while(index++ <= END) {
        retcode = recv(sock_fd, &c, 1, 0);
        if(retcode == -1) {
            perror("Error reading from server..");
            return -1;
        }
        printf("%c", c);
    }

    close(sock_fd);
    
}