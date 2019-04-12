#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

int main(int argc, char** argv){
  int sockfd, n;
  extern int errno;
  struct sockaddr_in local_addr, dest_addr;
  char sendline[100];
  char recvline[100];
  char message[100];

  if(argc != 3){
    printf("Errore! Inserisci IP_addres e PORT_number\n");
    return -1;
  }

  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    printf("Errore nell'apertura del socket!");
    return -1;
  }

  memset(&dest_addr, 0, sizeof(dest_addr));
  dest_addr.sin_family = AF_INET;
  dest_addr.sin_addr.s_addr = inet_addr(argv[1]);
  dest_addr.sin_port = htons(atoi(argv[2]));

  connect(sockfd, (struct sockaddr*) &dest_addr,sizeof(dest_addr));

  while(1){
    printf("Inserisci un messaggio: ");
    fgets(message, 100, stdin);
    send(sockfd, message, strlen(message), 0);
    memset(message, 0, sizeof(message));
  }
}
