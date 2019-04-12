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
  int sockfd, fd;
  extern int errno;
  struct sockaddr_in local_addr, remote_addr;
  socklen_t len;
  int conn;
  char message[100] = "";

  if(argc < 2){
    printf("Errore! Inserire la porta da ascoltare\n");
    return -1;
  }

  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    printf("Errore nell'apertura del socket!");
    return -1;
  }

  memset((char*)&local_addr, 0, sizeof(local_addr));
  local_addr.sin_family = AF_INET;
  local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  local_addr.sin_port = htons(atoi(argv[1]));
// local_addr.sin_family = AF_INET;local_addr.sin_addr.s_addr = htonl(INADDR_ANY);local_addr.sin_port = htons(atoi(argv[1])
  if(bind(sockfd, (struct sockaddr*) &local_addr, sizeof(local_addr)) < 0){
    printf("Errore nel binding! Errore %d\n", errno);
    return -1;
  }

  listen(sockfd, 5);
    while(conn = accept(sockfd,(struct sockaddr*) NULL, NULL)){
      int pid;
      if((pid = fork()) == 0){
        while(recv(conn, message, 100, 0) > 0){
          printf("Messaggio ricevuto: %s\n", message);
          memset(message, 0, sizeof(message));
        }
        exit(0);
      }
    }
  }
