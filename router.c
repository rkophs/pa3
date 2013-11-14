#include "dependencies/shared_.h"

int bindListener(struct Connection *connect) {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error opening socket");
        return -1;
    }

    int val = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof (val)) < 0) {
        printf("Error setting reuse addr\n");
        return -1;
    }

    struct sockaddr_in srcAddr;
    bzero(&srcAddr, sizeof (srcAddr));
    srcAddr.sin_family = AF_INET;
    srcAddr.sin_port = connect->srcPort;
    srcAddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr *) &srcAddr, sizeof (srcAddr)) < 0) {
        printf("Could not bind\n");
        return -1;
    }
    if (listen(sockfd, 20) < 0) { //Test this after all is working
        printf("could not listen\n");
        return -1;
    }
    return sockfd;
}

int bindConnector(struct Connection *connect) {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error opening socket");
        return -1;
    }

    int val = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof (val)) < 0) {
        printf("Error setting reuse addr\n");
        return -1;
    }

    struct sockaddr_in destAddr;
    bzero(&destAddr, sizeof (destAddr)); //zero the struct
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = connect->destPort;

    if (connect(sockfd, (struct sockaddr *) &destAddr, sizeof (destAddr)) < 0) {
        printf("Could not connect!\n");
        return -1;
    }
    return sockfd;
}

int main(int argc, char **argv) {

    struct Engine* engine = startEngine(argc, argv);

    struct Sockets {
        int lSock = -1; //local socket
        int rSock = -1; //remote: Only used for listeners
        int type = -1; //0: connect 1:listener
        int srcPort = -1;
        int dstPort = -1;
    };
    int it = 0;
    
    struct Sockets socks[engine->router->neighborCount];
    
    struct Connection *connect;
    
    
    //Bind listeners first
    while (connect != NULL) {
        if ((connect = engineNextNeighbor(engine)) != NULL) {
            if (connect->srcPort > connect->destPort) { //Listen
                int i;
                if ((i = bindListener(connect)) < 0) {
                    return -1;
                }
                socks[it].dstPort = connect->destPort;
                socks[it].srcPort = connect->srcPort;
                socks[it].type = 1;
                socks[it].lSock = i; //ServerFD
                it++;
            }
        }
    }
    
    //Now sleep and establish connectors:
    sleep(10);
    do {
        if((connect = engineNextNeighbor(engine)) != NULL){
            if(connect->srcPort < connect->destPort) { //Connect
                int i;
                if ((i = bindConnector(connect)) < 0){
                    //Already waited many seconds, just end now.
                    return -1;
                }
                socks[it].dstPort = connect->destPort;
                socks[it].srcPort = connect->srcPort;
                socks[it].lSock = i;
                socks[it].type = 0;
                it++;
            }
        }
    } while (connect != NULL);
    
    //Now accept connectors:
    


    releaseEngine(engine);
    return 0;
}