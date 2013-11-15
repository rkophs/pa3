#include "shared_.h"

struct Engine {
    struct Connection* connection;
    struct LSP* router;
    struct lspPool* lsps;
    struct RoutePool* routes;
    struct ARGS *args;
    struct Sockets *socks;
    int startTime;
    int it;
};

struct Connection *initConnection() {
    struct Connection *tmp;
    if ((tmp = (struct Connection *) malloc(sizeof (struct Connection))) == NULL) {
        return NULL;
    }
    tmp->destPort = -1;
    tmp->srcPort = -1;
}

struct Engine *initEngine(struct LSP* router, struct ARGS *args) {
    struct Engine *tmp;
    if ((tmp = (struct Engine *) malloc(sizeof (struct Engine))) == NULL) {
        return NULL;
    }
    if ((tmp->lsps = createLSPPool()) == NULL) {
        free(tmp);
        return NULL;
    }
    if ((tmp->routes = initRoutePool(router->sourceName, strlen(router->sourceName))) == NULL) {
        releaseLSPPool(tmp->lsps);
        free(tmp);
        return NULL;
    }
    if ((tmp->connection = initConnection()) == NULL) {
        releaseLSPPool(tmp->lsps);
        releaseRoutePool(tmp->routes);
        free(tmp);
        return NULL;
    }
    tmp->router = router;
    tmp->it = 0;
    tmp->args = args;
    tmp->socks = NULL;
    tmp->startTime = time(0);

    return tmp;
}

struct Engine *startEngine(int argc, char **argv) {
    /* Parse and save arguments */
    struct ARGS *args;
    if ((args = initArgs(argc, argv)) == NULL) {
        printf("Error parsing arguments\n");
        return NULL;
    }

    /* Instantiate Router LSP and a copy:*/
    struct LSP *routerLSP;
    struct LSP *nLSP;
    if ((routerLSP = parseInitFile(args)) == NULL) {
        printf("Error copying file information\n");
        free(args);
        return NULL;
    }
    if ((nLSP = parseInitFile(args)) == NULL) {
        printf("Error copying file information\n");
        releaseLSP(routerLSP);
        free(args);
        return NULL;
    }

    /* Set up engine with the router information & add copy LSP to engine pool*/
    struct Engine *engine;
    if ((engine = initEngine(routerLSP, args)) == NULL) {
        releaseLSP(routerLSP);
        releaseLSP(nLSP);
        free(args);
        return NULL;
    }

    engineProcessLSP(engine, nLSP);
    return engine;
}

void engineNextNeighbor(struct Engine *engine) {
    struct Node *tmp;
    tmp = NULL;
    if ((tmp = getNeighborByIt(engine->router, engine->it)) == NULL) {
        engine->it = 0;
        engine->connection->srcPort = -1;
        engine->connection->destPort = -1;
        return;
    }
    engine->it++;
    engine->connection->srcPort = tmp->srcPort;
    engine->connection->destPort = tmp->destPort;

}

int engineSyncRouters(struct Engine *engine) {
    if ((engine->socks = initSocksPool(engine->router->neighborCount)) == NULL) {
        return -1;
        printf("issue\n");
    }

    //Bind listeners first
    int it = 0;
    engineNextNeighbor(engine);
    while (engine->connection->srcPort > 0 && engine->connection->destPort > 0) {
        printf("%i %i\n", engine->connection->srcPort, engine->connection->destPort);
        if (engine->connection->srcPort > engine->connection->destPort) { //Listen
            int i;
            if ((i = bindListener(engine->connection)) < 0) {
                printf("error binding listener");
                return -1;
            }
            engine->socks[it].dstPort = engine->connection->destPort;
            engine->socks[it].srcPort = engine->connection->srcPort;
            engine->socks[it].type = 1;
            engine->socks[it].lSock = i; //ServerFD
            it++;
        }
        engineNextNeighbor(engine);
    }

    //Now sleep and establish connectors:
    sleep(10);
    engineNextNeighbor(engine);
    while (engine->connection->srcPort > 0 && engine->connection->destPort > 0) {
        if (engine->connection->srcPort < engine->connection->destPort) { //Connect
            int i;
            if ((i = bindConnector(engine->connection)) < 0) {
                //Already waited many seconds, just end now.
                return -1;
            }
            engine->socks[it].dstPort = engine->connection->destPort;
            engine->socks[it].srcPort = engine->connection->srcPort;
            engine->socks[it].rSock = i;
            engine->socks[it].type = 0;
            fcntl(i, F_SETFL, O_NONBLOCK);
            printf("Connected 1: %i\n", engine->socks[it].dstPort);
            it++;
        }
        engineNextNeighbor(engine);
    }

    //Now accept connectors:
    it = 0;
    for (it = 0; it < engine->router->neighborCount; it++) {
        if (engine->socks[it].type) { //Listener
            struct sockaddr_in remote;
            bzero(&remote, sizeof (remote));
            int rlen = sizeof (remote);
            int i;
            if ((i = accept(engine->socks[it].lSock, (struct sockaddr *) &remote, &rlen)) < 0) {
                //Error
                return -1;
            }
            fcntl(i, F_SETFL, O_NONBLOCK);
            printf("Connected 2: %i\n", engine->socks[it].dstPort);
            engine->socks[it].rSock = i;
        }
    }

    printf("End of sync\n");
    return 0;
}

int engineProcessLSP(struct Engine *engine, struct LSP *lsp) {
    if ((!strcmp(lsp->sourceName, engine->router->sourceName))
            && getLSPByName(engine->lsps, lsp->sourceName) != NULL) {
        releaseLSP(lsp);
        return -2; //Received LSP is of current router, just drop it.
    }

    int i = lspPoolCtrl(engine->lsps, lsp);
    if (i == 1 || i == 2 || i == 3) {
        //LSP was either added or updated or deleted:
        dijkstrasEngine(engine->routes, engine->lsps);
        int buffSize = 2048;
        char buff[buffSize];
        bzero(buff, buffSize);
        BuffRouteTable(engine->routes, buff, buffSize);
        bzero(buff, buffSize);
        BuffAllLSPs(engine->lsps, buff, buffSize);
    }

    return i;
}

void engineDie(struct Engine *engine) {
    int it;
    for (it = 0; it < engine->router->neighborCount; it++) {
        char buff[4];
        bzero(buff, 4);
        strcpy(buff, "*");
        send(engine->socks[it].rSock, &buff, 4, 0);
    }
}

void engineSendLSP(struct Engine *engine) {
    incSeqNum(engine->router);
    int buffSize = 1024;
    char buff[buffSize];
    bzero(buff, buffSize);
    BuffLSP(engine->router, buff, buffSize);
    int it;
    for (it = 0; it < engine->router->neighborCount; it++) {
        send(engine->socks[it].rSock, &buff, strlen(buff), 0);
    }
}

void engineForwardLSP(struct Engine* engine, struct LSP *lsp){
    int buffSize = 1024;
    char buff[buffSize];
    bzero(buff, buffSize);
    BuffLSP(lsp, buff, buffSize);
    int it;
    for (it = 0; it < engine->router->neighborCount; it++) {
        send(engine->socks[it].rSock, &buff, strlen(buff), 0);
    }
}

int engineRecv(struct Engine *engine) {
    int it;
    for (it = 0; it < engine->router->neighborCount; it++) {
        int buffSize = 2048;
        char buff[buffSize];
        bzero(buff, buffSize);
        if (recv(engine->socks[it].rSock, buff, sizeof (buff), 0) > 0) {
            int it2 = 0;
            int die = 0;
            struct LSP *lsp;
            if ((lsp = parsePacket(buff, buffSize, &it2, &die)) != NULL) {
                char tmp[1024];
                bzero(tmp, 1024);
                BuffLSP(lsp, tmp, 1024);
                int i = engineProcessLSP(engine, lsp);
                if(i == 1 || 1 == 2){
                    engineForwardLSP(engine, lsp);
                }
                if(i == -1){
                    return -1;
                }
            }
            if (die) {
                engineDie(engine);
                return 0;
            }
        }
    }
    return 1;
}

int engineRun(struct Engine *engine) {
    int t = time(0);
    while (1) {
        if (engine->args->destroyTime != -1
                && (t - engine->startTime >= engine->args->destroyTime)) {
            engineDie(engine);
            //return 0;
        }
        if (t + 5 < time(0)) {
            t = time(0);
            engineSendLSP(engine);
        }

        if (engineRecv(engine) == 0) {
            return 0;
        }
    }
}

int restartEngine(struct Engine *engine) {
    releaseAllRoutes(engine->routes);
    releaseAllLSPs(engine->lsps);
    engine->it = 0;
}

void releaseEngine(struct Engine *engine) {
    releaseLSPPool(engine->lsps); //Also releases the routerLSP!!!
    releaseRoutePool(engine->routes);
    releaseLSP(engine->router);
    releaseSocksPool(engine->socks);
    free(engine->args);
    free(engine->connection);
    engine->connection = NULL;
    free(engine);
    engine = NULL;
}