#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#define SERVERPORT 7777
#define SERVERNAME "127.0.0.1"
#define MAXMESSAGE 2000
#define MAXBUF 1024

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
char buffer[MAXBUF];
char client_message[MAXMESSAGE];

void * connection_handler(void * arg) {
    int client_socket = *( (int*) arg);
    recv(client_socket, &client_message, MAXMESSAGE, 0);

    // Send message to client socket
    pthread_mutex_lock(&mutex);
    char *message = malloc(sizeof(client_message) + 20);
    strcpy(message, "Hello Client: ");
    strcat(message, client_message);
    strcat(message, "\n");
    strcpy(buffer, message);
    free(message);
    pthread_mutex_unlock(&mutex);
    sleep(10);
    send(client_socket, buffer, sizeof(buffer), 0);
    printf("Exit socketThread\n");
    close(client_socket);
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    setbuf(stdout, NULL);
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len;
    int retcode;

    // Create server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket == -1) {
        perror("Error creating server socket..");
        return -1;
    }

    // Set server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVERPORT);
    inet_aton(SERVERNAME, &server_addr.sin_addr);

    // Bind address to socket
    retcode = bind(server_socket, (struct sockaddr*) &server_addr, sizeof(server_addr));
    if(retcode == -1) {
        perror("Error binding addresso to socket..");
        return -1;
    }

    // Make the socket listen for connections
    retcode = listen(server_socket, 3);
    if(retcode == -1) {
        perror("Error on listen..");
        return -1;
    }

    printf("Server ready and running. Listening on port %d", SERVERPORT);

    // Accept connections
    client_addr_len = sizeof(client_addr);
    pthread_t thread_id[60];
    int i = 0;

    while(1) {
        client_socket = accept(server_socket, (struct sockaddr*) &client_addr, &client_addr_len);

        if(client_socket == -1) {
            perror("Error accepting connection..");
            return -1;
        }

        printf("\nConnection with client@%s", inet_ntoa(client_addr.sin_addr));

        // Create a thread for each client request
        if(pthread_create(&thread_id[i++], NULL, connection_handler, (void*) &client_socket) != 0) {
            perror("Error creating thread..");
            return -1;
        }

        printf("\nThread %d accepted request", i);
        if(i >= 50) {
            i = 0;
            while(i <= 50) {
                pthread_join(thread_id[i++], NULL);
            }
            i = 0;
        }

    }

    return 0;
}