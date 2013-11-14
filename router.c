#include "dependencies/shared_.h"

int bindListener(/*struct Connection *connect*/char* port) {
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
    srcAddr.sin_port = htons(atoi(port)); //connect->srcPort;
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

int bindConnector(/*struct Connection *connect*/char* port) {
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
    destAddr.sin_port = htons(atoi(port)); // connect->destPort;

    if (connect(sockfd, (struct sockaddr *) &destAddr, sizeof (destAddr)) < 0) {
        printf("Could not connect!\n");
        return -1;
    }
    return sockfd;
}

int main(int argc, char **argv) {

    //struct Engine* engine = startEngine(argc, argv);

    int s1;
    if ((s1 = bindConnector(argv[1])) < 0) {
        //Error connecting... now try listening:
        int s2;
        if ((s2 = bindListener(argv[2])) < 0) {
            //error listening
        } else {
            int temp;
            struct sockaddr_in remote;
            bzero(&remote, sizeof(remote));
            int len = sizeof(remote);
            if((temp = accept(s2, (struct sockaddr *)&remote, &len)));
            printf("Connected as a listener s2: %i, temp: %i\n", s2, temp);
        }
    } else {
        printf("Connected as a connector!\n");
    }


    //releaseEngine(engine);
    return 0;
}