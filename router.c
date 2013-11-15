#include "dependencies/shared_.h"

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

struct Sockets {
    int lSock; //local socket
    int rSock; //remote: Only used for listeners
    int type; //0: connect 1:listener
    int srcPort;
    int dstPort;
};

int main(int argc, char **argv) {

    struct Engine* engine = startEngine(argc, argv);

    int it = 0;

    struct Sockets *socks;
    if((socks = (struct Sockets *) malloc(sizeof(struct Sockets)*engine->router->neighborCount)) == NULL){
        return -1;
    }
    for(it = 0; it < engine->router->neighborCount; it++){
        socks[it].lSock = -1;
        socks[it].rSock = -1;
        socks[it].type = -1;
        socks[it].srcPort = -1;
        socks[it].dstPort = -1;
    }

    it = 0;
    struct Connection *connection;


    //Bind listeners first
    do {
        if ((connection = engineNextNeighbor(engine)) != NULL) {
            if (connection->srcPort > connection->destPort) { //Listen
                int i;
                if ((i = bindListener(connection)) < 0) {
                    return -1;
                }
                socks[it].dstPort = connection->destPort;
                socks[it].srcPort = connection->srcPort;
                socks[it].type = 1;
                socks[it].lSock = i; //ServerFD
                it++;
            }
        }
    } while (connection != NULL);

    //Now sleep and establish connectors:
    sleep(20);
    do {
        if ((connection = engineNextNeighbor(engine)) != NULL) {
            if (connection->srcPort < connection->destPort) { //Connect
                int i;
                if ((i = bindConnector(connection)) < 0) {
                    //Already waited many seconds, just end now.
                    return -1;
                }
                socks[it].dstPort = connection->destPort;
                socks[it].srcPort = connection->srcPort;
                socks[it].lSock = i;
                socks[it].type = 0;
                it++;
            }
        }
    } while (connection != NULL);

    //Now accept connectors:
    it = 0;
    for (it = 0; it < engine->router->neighborCount; it++) {
        if (socks[it].type) { //Listener
            struct sockaddr_in remote;
            bzero(&remote, sizeof (remote));
            int rlen = sizeof (remote);
            int i;
            if ((i = accept(socks[it].lSock, (struct sockaddr *) &remote, &rlen)) < 0) {
                //Error
                return -1;
            }
            socks[it].rSock = i;
        }
    }


    releaseEngine(engine);
    return 0;
}