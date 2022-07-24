#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define N 13
#define IN 256

struct nodeinfo
{
    int source;
    int target;
    int adj;
    char path[1024];
};


void check_err(int retcode, char* message) {
    if (retcode < 0) {
        printf("%s\n", message);
        exit(-1);
    }
}

char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}

void add_routing_R1() {
    system("ip route add 1.1.2.2 via 1.1.13.29 dev enp0s9");
    system("ip route add 1.1.3.3 via 1.1.13.29 dev enp0s9");
    system("ip route add 1.1.4.4 via 1.1.13.32 dev enp0s10");
    system("ip route add 1.1.5.5 via 1.1.13.4 dev enp0s8");
    system("ip route add 1.1.6.6 via 1.1.13.29 dev enp0s9");
    system("ip route add 1.1.7.7 via 1.1.13.4 dev enp0s8");
    system("ip route add 1.1.8.8 via 1.1.13.4 dev enp0s8");
    system("ip route add 1.1.9.9 via 1.1.13.32 dev enp0s10");
    system("ip route add 1.1.10.10 via 1.1.13.32 dev enp0s10");
    system("ip route add 1.1.11.11 via 1.1.13.32 dev enp0s10");
    system("ip route add 1.1.12.12 via 1.1.13.4 dev enp0s8");
    printf("Routing for R1 completed!\n");
}

void add_routing_R2() {
    system("ip route add 1.1.1.1 via 1.1.13.8 dev enp0s8");
    system("ip route add 1.1.3.3 via 1.1.13.21 dev enp0s10");
    system("ip route add 1.1.4.4 via 1.1.13.21 dev enp0s10");
    system("ip route add 1.1.5.5 via 1.1.13.25 dev enp0s9");
    system("ip route add 1.1.6.6 via 1.1.13.21 dev enp0s10");
    system("ip route add 1.1.7.7 via 1.1.13.8 dev enp0s8");
    system("ip route add 1.1.8.8 via 1.1.13.25 dev enp0s9");
    system("ip route add 1.1.9.9 via 1.1.13.21 dev enp0s10");
    system("ip route add 1.1.10.10 via 1.1.13.8 dev enp0s8");
    system("ip route add 1.1.11.11 via 1.1.13.25 dev enp0s9");
    system("ip route add 1.1.12.12 via 1.1.13.8 dev enp0s8");
    printf("Routing for R2 completed!\n");
}

struct nodeinfo* dijsktra(int cost[][N], int source, int target)
{
    struct nodeinfo* info = malloc(sizeof(*info));
    memset(info, 0, sizeof(*info));
    int dist[N], prev[N], selected[N] = {0};
    int m, min, start, d;
    char* path = malloc(sizeof(char) * 1024);

    memset(path, '\0', sizeof(path));
    // Initialize
    for (int i=1;i< N;i++) {
        dist[i] = IN;
        prev[i] = -1;
    }

    start = source;
    selected[start] = 1;
    dist[start] = 0;

    // Start main cycle
    while (selected[target] == 0) {
        min = IN;
        m = 0;
        for (int i=1;i< N;i++) {
            d = dist[start] + cost[start][i];
            if (d < dist[i] && selected[i]==0) {
                dist[i] = d;
                prev[i] = start;
            }
            if (min > dist[i] && selected[i]==0) {
                min = dist[i];
                m = i;
            }
        }
        start = m;
        selected[start] = 1;
    }

    start = target;
    char* tmp = malloc(sizeof(char)*1024);

    while (start != -1) {
        memset(tmp, '\0', sizeof(tmp));
        sprintf(tmp, "%d ", start); // print index
        strncat(path, tmp, strlen(tmp));
        if (prev[start] == source)
            info->adj = start;
        start = prev[start];
    }

    free(tmp);
    //printf("Minimum path between %d and %d: '%s'\n",source, target, path);
    
    memcpy(info->path, path, sizeof(path));
    info->source = source;
    info->target = target;

    //printf("Struct source: %d\nStruct target: %d\nStruct path: %s\nStruct adj: %d\n", info->source, info->target, info->path, info->adj);

    
    return info;
}

void setup_routes(struct nodeinfo* info) {

    if (info->source == info->target)
        return;

    char* destination = malloc(sizeof(char)*1024);
    //char* router_address = malloc(sizeof(char)*1024);
    memset(destination, '\0', sizeof(destination));
    //memset(router_address, '\0', sizeof(router_address));

    sprintf(destination, "1.1.%d.%d", info->target, info->target);
    printf("ip route add %s via ${ROUTER ADDRESS} dev ${ROUTER INTERFACE}\n", destination);

    // HERE ADD THE STATIC ADDRESS OF ROUTERS
    // BASED ON info->source and info->target
    // CREATE STATIC VARIABLES LIKE 1_7 = ${ADDRESS OF ROUTER 7} dev ${INTERFACE OF THE ROUTER}

    free(destination);
    //free(router_address);
}

int main(int argc, char** argv) {
    struct nodeinfo* info;
    int adj[13][13] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0}, // 0 index not used
        {IN,1,IN,1,IN,IN,IN,1,IN,IN,1,IN,IN},
        {IN,IN,1,IN,IN,IN,1,IN,1,IN,IN,IN,1},
        {IN,1,IN,1,IN,IN,1,1,IN,IN,IN,IN,IN},
        {IN,IN,IN,IN,1,IN,IN,IN,IN,1,IN,IN,IN},
        {IN,IN,IN,IN,IN,1,IN,IN,1,IN,IN,1,1},
        {IN,IN,1,1,1,IN,1,IN,IN,IN,IN,IN,IN},
        {IN,1,IN,1,IN,IN,IN,1,IN,IN,IN,IN,1},
        {IN,IN,1,IN,IN,1,IN,IN,1,IN,IN,IN,IN},
        {IN,IN,IN,IN,1,IN,IN,IN,IN,1,IN,1,IN},
        {IN,1,IN,IN,1,IN,IN,IN,IN,IN,1,IN,IN},
        {IN,IN,IN,IN,IN,1,IN,IN,IN,1,IN,1,IN},
        {IN,IN,1,IN,IN,1,IN,1,IN,IN,IN,IN,1}
    };

    if (argc < 2) {
        printf("USAGE: %s <router-number>\n", argv[0]);
        return -1;
    }

    for (int i=1; i<13; i++) {
        for (int j=1; j<13; j++) {
            //memset(path, 0, sizeof(path));
            info = dijsktra(adj, i, j);
            setup_routes(info);
        }
    }


}