#include "parser_.h"

struct Connection {
    int srcPort;
    int destPort;
};

struct Engine {
    struct Connection* connect;
    struct LSP* router;
    struct lspPool* lsps;
    struct RoutePool* routes;
    struct ARGS *args;
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
    if((tmp->connect = initConnection()) == NULL){
        releaseLSPPool(tmp->lsps);
        releaseRoutePool(tmp->routes);
        free(tmp);
        return NULL;
    }
    tmp->router = router;
    tmp->it = 0;
    tmp->args = args;
    
    return tmp;
}

struct Engine *startEngine(int argc, char **argv){
    /* Parse and save arguments */
    struct ARGS *args;
    if((args = initArgs(argc, argv)) == NULL){
        printf("Error parsing arguments\n");
        return NULL;
    }
    
    /* Instantiate Router LSP and a copy:*/
    struct LSP *routerLSP;
    struct LSP *nLSP;
    if((routerLSP = parseLSP(args)) == NULL){
        printf("Error copying file information\n");
        free(args);
        return NULL;
    }
    if((nLSP = parseLSP(args)) == NULL){
        printf("Error copying file information\n");
        releaseLSP(routerLSP);
        free(args);
        return NULL;
    }
    
    /* Set up engine with the router information & add copy LSP to engine pool*/
    struct Engine *engine;
    if((engine = initEngine(routerLSP, args)) == NULL){
        releaseLSP(routerLSP);
        releaseLSP(nLSP);
        free(args);
    }
    
    engineProcessLSP(engine, nLSP);
    return engine;
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
    free(engine->args);
    free(engine->connect);
    engine->connect = NULL;
    free(engine);
    engine = NULL;
}