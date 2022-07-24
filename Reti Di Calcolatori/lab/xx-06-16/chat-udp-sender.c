/**
 * https://drive.google.com/drive/u/0/folders/1NyNUv5JiXgBSPYWPobFnsKlVxVHuMqr6
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define LISTENING_PORT 47856
#define BUFF_SIZE 80

void check_err(int retcode, char* message) {
    if (retcode < 0) {
        printf("%s\n", message);
        exit(-1);
    }
}

int main(int argc, char** argv) {
    int sockfd, retcode;
    struct sockaddr_in client_addr, srv_addr;
    socklen_t len = sizeof(client_addr);
    char buffer[BUFF_SIZE];
    char confirmation[BUFF_SIZE];

    sprintf(confirmation, "CONFIRMATION MESSAGE");

    if (fork() == 0) {
        // Listening 
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        check_err(sockfd, "error on socket creation");

        memset(&srv_addr, 0, len);
        srv_addr.sin_family = AF_INET;
        srv_addr.sin_port = htons(LISTENING_PORT);
        srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

        retcode = bind(sockfd, (struct sockaddr*) &srv_addr, len);
        check_err(retcode, "error on binding socket");

        while (1) {
            retcode = recvfrom(sockfd, buffer, BUFF_SIZE-1, 0, (struct sockaddr*) &client_addr, &len);
            check_err(retcode, "error on receiving");
            buffer[retcode] = '\0';
            printf("%s sent you: '%s'\n", inet_ntoa(client_addr.sin_addr), buffer);
            retcode = sendto(sockfd, confirmation, sizeof(confirmation), 0, (struct sockaddr*) &client_addr, len);
            check_err(retcode, "error on sending message confirmation");
            printf("Confirmation message sent!\n");
        }
    }
    else {
        // Sender
        int choice;
        FILE* file_ptr;
        char* line = malloc(sizeof(char) * 1024);
        char* destination = malloc(sizeof(char) * BUFF_SIZE);
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        check_err(sockfd, "error on socket creation");

        file_ptr = fopen("./users.txt", "r");
        if (file_ptr == NULL) {
            printf("error on opening file\n");
            exit(-1);
        }

        // Make the user choose the destination
        memset(line, '\0', sizeof(line));
        memset(destination, '\0', sizeof(destination));
        printf("Choose the destinatary: \n");
        while (fgets(line, 1024, file_ptr) != NULL) {
            printf("%s", line);
        }

        printf("\nInsert user number here: ");
        scanf("%d", &choice);
        sprintf(destination, "10.0.0.%d", choice+1);
        

        printf("You chose: %s\n", destination);
        memset(&srv_addr, 0, len);
        srv_addr.sin_family = AF_INET;
        srv_addr.sin_port = htons(LISTENING_PORT);
        srv_addr.sin_addr.s_addr = inet_addr(destination);
        

        
        printf("You can start messaging: ");
        while (fgets(buffer, BUFF_SIZE, stdin) != NULL) {
            printf("\nSending %s to %s\n", buffer, destination);

            retcode = sendto(sockfd, buffer, BUFF_SIZE, 0, (struct sockaddr*) &srv_addr, len);
            check_err(retcode, "error on sending message");

            printf("Message succesfully sent, now waiting for a confirmation.\n");

            memset(buffer, '\0', BUFF_SIZE);
            retcode = recvfrom(sockfd, buffer, BUFF_SIZE-1, 0, (struct sockaddr*) &srv_addr, &len);
            check_err(retcode, "error on receiving confirmation");
            buffer[retcode] = '\0';
            printf("Confirmation received\n");
        }
    }
}