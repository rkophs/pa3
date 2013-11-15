#include "parser_.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

struct Connection {
    int srcPort;
    int destPort;
};

struct Sockets {
    int lSock; //local socket
    int rSock; //remote: Only used for listeners
    int type; //0: connect 1:listener
    int srcPort;
    int dstPort;
};

struct Sockets *initSocksPool(int count){
    int it;
    struct Sockets *socks;
    if((socks = (struct Sockets *) malloc(sizeof(struct Sockets)*count)) == NULL){
        return NULL;
    }
    for(it = 0; it < count; it++){
        socks[it].lSock = -1;
        socks[it].rSock = -1;
        socks[it].type = -1;
        socks[it].srcPort = -1;
        socks[it].dstPort = -1;
    }
    return socks;
}
int bindListener(struct Connection *connection) {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return -1;
    }

    int val = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof (val)) < 0) {
        return -1;
    }

    struct sockaddr_in srcAddr;
    bzero(&srcAddr, sizeof (srcAddr));
    srcAddr.sin_family = AF_INET;
    srcAddr.sin_port = connection->srcPort;
    srcAddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr *) &srcAddr, sizeof (srcAddr)) < 0) {
        return -1;
    }
    if (listen(sockfd, 20) < 0) { //Test this after all is working
        return -1;
    }
    return sockfd;
}

int bindConnector(struct Connection *connection) {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return -1;
    }

    int val = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof (val)) < 0) {
        return -1;
    }

    struct sockaddr_in destAddr;
    bzero(&destAddr, sizeof (destAddr)); //zero the struct
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = connection->destPort;

    if (connect(sockfd, (struct sockaddr *) &destAddr, sizeof (destAddr)) < 0) {
        return -1;
    }
    return sockfd;
}

void releaseSocksPool(struct Sockets *socks){
    if(socks == NULL){
        return;
    }
    free(socks);
    socks = NULL;
}