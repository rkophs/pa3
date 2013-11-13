#include "routePool_.h"

struct Connection {
    int srcPort;
    int destPort;
};

struct Engine {
    struct Connection* connect;
    struct LSP* router;
    struct lspPool* lsps;
    struct RoutePool* routes;
    int it;
};

struct Connection *initConnection(){
    struct Connection *tmp;
    if((tmp = (struct Connection *) malloc(sizeof(struct Connection))) == NULL){
        return NULL;
    }
    tmp->destPort = 0;
    tmp->srcPort = 0;
}

struct Engine *initEngine(char *name, int nameSize, struct LSP* router) {
    struct Engine *tmp;
    if ((tmp = (struct Engine *) malloc(sizeof (struct Engine))) == NULL) {
        return NULL;
    }
    if ((tmp->lsps = createLSPPool()) == NULL) {
        free(tmp);
        return NULL;
    }
    if ((tmp->routes = initRoutePool(name, nameSize)) == NULL) {
        releaseLSPPool(tmp->lsps);
        free(tmp);
        return NULL;
    }
    if((tmp->connect = initConnection()) == NULL){
        releaseLSPPool(tmp->lsps);
        releaseRoutePool(tmp->routes);
        free(tmp);
        return NULL;
    }
    tmp->router = router;
    tmp->it = 0;
    
    return tmp;
}

int engineProcessLSP(struct Engine *engine, struct LSP *lsp) {
    if((!strcmp(lsp->sourceName, engine->router->sourceName)) 
            && getLSPByName(engine->lsps, lsp->sourceName) != NULL){
        releaseLSP(lsp);
        return -2; //Received LSP is of current router, just drop it.
    }
    
    int i = lspPoolCtrl(engine->lsps, lsp);
    if(i == 1 || i == 2 || i == 3){
        //LSP was either added or updated or deleted:
        dijkstrasEngine(engine->routes, engine->lsps);
    }
    
    return i;
}

struct Connection *engineNextNeighbor(struct Engine *engine){
    struct Node *tmp;
    tmp = NULL;
    if((tmp = getNeighborByIt(engine->router, engine->it)) == NULL){
        engine->it = 0;
        return NULL;
    }
    engine->it++;
    engine->connect->srcPort = tmp->srcPort;
    engine->connect->destPort = tmp->destPort;
    
    return engine->connect;
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
    free(engine->connect);
    engine->router = NULL;
    engine->lsps = NULL;
    engine->routes = NULL;
    free(engine);
    engine = NULL;
}