
#include "lspPool_.h"

struct Route {
    char dest[32];
    int cost;
    int srcPort;
    int destPort;
    int confirmed;
};

struct Map {
    char name[32];
};

struct RoutePorts {
    int src;
    int dest;
};

struct RoutePool {
    char name[32];
    int count;
    int mapCount;
    struct Route *route;
    struct Map *map;
};

//Public:

struct RoutePool *initRoutePool(char *name, int nameSize) {
    struct RoutePool *tmp;
    if ((tmp = (struct RoutePool *) malloc(sizeof (struct RoutePool))) == NULL) {
        return NULL;
    }

    bzero(tmp->name, sizeof (tmp->name));
    if (sizeof (tmp->name) <= nameSize) {
        free(tmp);
        return NULL;
    }
    strncpy(tmp->name, name, nameSize);
    tmp->count = 0;
    tmp->route = NULL;
    tmp->map = NULL;
    tmp->mapCount = 0;
    return tmp;
}

//Public

void releaseAllRoutes(struct RoutePool *pool) {
    if (pool == NULL) { //Not a header
        return;
    }
    if (pool->route != NULL){
        free(pool->route);
    }
    if (pool->map != NULL){
        free(pool->map);
    }
    pool->count = 0;
    pool->mapCount = 0;
    pool->route = NULL;
    pool->map = NULL;
}

//Public

void releaseRoutePool(struct RoutePool *pool) {
    if (pool == NULL) {
        return;
    }

    releaseAllRoutes(pool);
    free(pool);
    pool = NULL;
}

//Private:

int getEntry(struct RoutePool *pool, char *entry) {
    if (pool == NULL) {
        return -1;
    }
    int i;
    for (i = 0; i < pool->mapCount; i++) {
        if (!strcmp(pool->map[i].name, entry)) {
            return i;
        }
    }
    return -1;
}

//Private:

int putEntry(struct RoutePool *pool, char *entry, int entrySize) {
    bzero(pool->map[pool->mapCount].name, sizeof (pool->map[pool->mapCount].name));
    strncpy(pool->map[pool->mapCount].name, entry, entrySize);
    pool->mapCount++;
}

//Private:

int generateNodes(struct RoutePool *routes, struct lspPool* lsps) {
    if (routes == NULL || lsps == NULL) {
        return -1;
    }
    
    releaseAllRoutes(routes);

    //Generate list of nodes:
    if ((routes->route = (struct Route *) malloc(sizeof (struct Route) * lsps->count)) == NULL) {
        return -1;
    }
    if ((routes->map = (struct Map *) malloc(sizeof (struct Map) * lsps->count)) == NULL) {
        free(routes->route);
        return -1;
    }

    routes->count = lsps->count;
    struct LSP *srcLsp = getLSPByName(lsps, routes->name); //Don't free up!

    //Put all names:
    int i;
    for (i = 0; i < routes->count; i++) {
        struct LSP *tmp = getLSPByIt(lsps, i); //Don't free up!
        if (getEntry(routes, tmp->sourceName) < 0) {
            //Entry doesn't exist
            bzero(routes->route[i].dest, sizeof (routes->route[i].dest));
            strncpy(routes->route[i].dest, tmp->sourceName, strlen(tmp->sourceName));
            routes->route[i].cost = -1;
            routes->route[i].destPort = -1;
            routes->route[i].srcPort = -1;
            routes->route[i].confirmed = -1;
            putEntry(routes, tmp->sourceName, strlen(tmp->sourceName));
        } else {
            return -1;
        }
    }

    //Copy loop-back (confirmed list):
    if ((i = getEntry(routes, routes->name)) >= 0) {
        bzero(routes->route[i].dest, sizeof (routes->route[i].dest));
        strncpy(routes->route[i].dest, routes->name, strlen(routes->name));
        routes->route[i].cost = 0;
        routes->route[i].destPort = 0;
        routes->route[i].srcPort = 0;
        routes->route[i].confirmed = 1;
    } else {
        return -1;
    }

    //Copy in tentative list:
    int j, k;
    for (i = 0; i < srcLsp->neighborCount; i++) {
        struct Node *neighbor = getNeighborByIt(srcLsp, i);
        if ((j = getEntry(routes, neighbor->name)) >= 0) {
            routes->route[j].cost = neighbor->cost;
            routes->route[j].destPort = neighbor->destPort;
            routes->route[j].srcPort = neighbor->srcPort;
            routes->route[j].confirmed = 0;
        } else {
            return -1;
        }
    }
    return 0;
}

struct LSP* getNextTentativeLSP(struct RoutePool *routes, struct lspPool *lsps) {
    int i;
    struct LSP *tmp = NULL;
    int lowCost = -1;
    for (i = 0; i < routes->count; i++) {
        if (routes->route[i].confirmed == 0) {
            if (lowCost == -1 && routes->route[i].cost != -1) {
                lowCost = routes->route[i].cost;
                tmp = getLSPByName(lsps, routes->route[i].dest);
            } else if (routes->route[i].cost < lowCost) {
                lowCost = routes->route[i].cost;
                tmp = getLSPByName(lsps, routes->route[i].dest);
            }
        }
    }
    return tmp;
}

int generateRoutes(struct RoutePool *routes, struct lspPool* lsps){
    struct LSP *nextLSP;
    int routeIt;
    if ((nextLSP = getNextTentativeLSP(routes, lsps)) == NULL) {
        return -1;
    }
    if ((routeIt = getEntry(routes, nextLSP->sourceName)) < 0) {
        return -1; // should never happen
    }
    routes->route[routeIt].confirmed = 1;

    int nextIt;
    while (1) {
        //Find the cost to the next node we are looking at:
        if ((nextIt = getEntry(routes, nextLSP->sourceName)) < 0) {
            return -1;
        }
        int costToNext = routes->route[nextIt].cost;
        if (costToNext < 0) {
            return -1; //This should never happen (infinity)
        }
        //Step 3:
        int i;
        for (i = 0; i < nextLSP->neighborCount; i++) { //Step 3;

            struct Node *neighbor = getNeighborByIt(nextLSP, i);
            if (neighbor == NULL) {
                return -1; //Should never happen
            }
            if ((routeIt = getEntry(routes, neighbor->name)) < 0) {
                return -1;
            }

            struct Route *neighborRoute = &routes->route[routeIt];
            int cost = neighbor->cost + costToNext;

            if (neighborRoute->confirmed == -1) { //not tentative nor confirmed:
                neighborRoute->confirmed = 0;
                neighborRoute->cost = cost;
                neighborRoute->destPort = routes->route[nextIt].destPort;
                neighborRoute->srcPort = routes->route[nextIt].srcPort;

            } else if (neighborRoute->confirmed == 0 &&
                    cost < neighborRoute->cost) { //tentative and lower cost:
                neighborRoute->cost = cost;
                neighborRoute->destPort = routes->route[nextIt].destPort;
                neighborRoute->srcPort = routes->route[nextIt].srcPort;
            } else if (neighborRoute->confirmed == 1) {
                continue;
            }
        }

        if ((nextLSP = getNextTentativeLSP(routes, lsps)) == NULL) {
            break;
        }
        if ((routeIt = getEntry(routes, nextLSP->sourceName)) < 0) {
            return -1; // should never happen
        }
        routes->route[routeIt].confirmed = 1;
    };
}

//Public
int dijkstrasEngine(struct RoutePool *routes, struct lspPool* lsps) {
    if(generateNodes(routes, lsps) < 0){ //Step 1.
        return -1;
    }
    return generateRoutes(routes, lsps);
}