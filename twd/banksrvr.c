#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>

#define MAXBUF 1024
#define SERVERNAME "localhost"
#define SERVERPORT 7777

char buffer[MAXBUF];
int conti[10];
int current_conto = 0;

int mkaddr(struct sockaddr_in* addr, const char* hostname_or_ip, u_int16_t port) {
    struct hostent* host;
    size_t nbytes;

    memset(addr, 0, sizeof(*addr));
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);

    if( (host = gethostbyname(hostname_or_ip)) == NULL) {
        herror("Querying");
        return -1;
    }

    memcpy( &(addr->sin_addr), host->h_addr_list[0], nbytes = host->h_length);
    return ((int) nbytes);
}

int get_conto_from_arg(char* msg) {
    int index = (int)msg[1] - (int)'0';
    return index;
}

int send_money(char* msg) {
    char* money_to_send = strtok(msg, "V");
    int money = atoi(money_to_send);
    printf("%d", money);
    conti[current_conto] = money;
    return money;
}

int get_money(char* msg) {
    char* money_to_get = strtok(msg, "P");
    int money = atoi(money_to_get);
    printf("%d", money);
    conti[current_conto] -= money;
    return money;
}


int main(int argc, char* argv[]) {
    setbuf(stdout, NULL);
    int server_socket, connection_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len;
    int retcode;

    // Create server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket == -1) {
        perror("Error on socket creation....");
        return -1;
    }

    // Translate address
    mkaddr(&server_addr, SERVERNAME, SERVERPORT);

    // Binding address to socket to get it online
    retcode = bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(retcode == -1) {
        perror("Error on binding...");
        return -1;
    }

    printf("---Server ready and listening on port %d---\n", SERVERPORT);

    // Listen for request
    retcode = listen(server_socket, 1);
    if(retcode == -1) {
        perror("Error on listening...");
        return -1;
    }

    // Accept connections
    client_addr_len = sizeof(client_addr);
    while(1) {
        connection_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
        if(connection_socket == -1) {
            perror("Error on accepting connection...");
            return -1;
        }

        printf("\nClient@%s connects on socket %d.\n", inet_ntoa(client_addr.sin_addr), connection_socket);

        // Start reading from socket
        if( (retcode = read(connection_socket, buffer, MAXBUF-1)) > 0) {
            buffer[retcode] = '\0';
            printf("Request: %s", buffer);
            int dollars;
            if(buffer[0] == 'U') {
                current_conto = get_conto_from_arg(buffer);
                printf("\nSei passato al conto %d, il saldo è: %d", current_conto, conti[current_conto]);
            }
            else if(buffer[0] == 'V') {
                dollars = send_money(buffer);
                printf("\n Hai appena depositato %d dollari nel conto %d", dollars, current_conto);
            }
            else if(buffer[0] == 'P'){
                dollars = get_money(buffer);
                printf("\nHai appena prelevato %d dollari dal conto %d.", dollars, current_conto);
            }
            else if(buffer[0] == 'S') {
                printf("\nIl saldo del conto %d è pari a: %d", current_conto, conti[current_conto]);
            }
            else 
                printf("ERROR: Il server accetta solamente i seguenti comandi:\n-[Un] dove n, da 0 a 9, è il numero del conto;\n-[Vxyzw] dove xyzw sono cifre intere;\n-[Pxyzw] dove xywz sono cifre intere;\n-[S]");
            close(connection_socket);
        }
    }

}