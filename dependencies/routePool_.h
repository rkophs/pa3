
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lspPool_.h"

struct Route {
    char dest[32];
    int cost;
    int srcPort;
    int destPort;
};

struct Map {
    char name[32];
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

//Public
void releaseAllRoutes(struct RoutePool *pool) {
    if (pool == NULL) { //Not a header
        return;
    }

    free(pool->route);
    free(pool->map);
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
int generateNodes(struct RoutePool *routes, struct lspPool* lsps) {
    if (routes == NULL || lsps == NULL) {
        return -1;
    }

    //Generate list of nodes:
    if ((routes->route = (struct Route *) malloc(sizeof (struct Route) * lsps->count)) == NULL) {
        return -1;
    }
    if ((routes->map = (struct Map *) malloc(sizeof (struct Map) * lsps->count)) == NULL) {
        free(routes->route);
        return -1;
    }
    
    routes->count = lsps->count;
    struct LSP *srcLsp = getNeighborsByName(lsps, routes->name); //Don't free up!
    
    //Put all names:
    int i;
    for (i = 0; i < routes->count; i++) {
        struct LSP *tmp = getNeighborsByIt(lsps, i); //Don't free up!
        if (getEntry(routes, tmp->sourceName) < 0) {
            //Entry doesn't exist
            bzero(routes->route[i].dest, sizeof (routes->route[i].dest));
            strncpy(routes->route[i].dest, tmp->sourceName, strlen(tmp->sourceName));
            routes->route[i].cost = -1;
            routes->route[i].destPort = -1;
            routes->route[i].srcPort = -1;
            putEntry(routes, tmp->sourceName, strlen(tmp->sourceName));
        } else {
            return -1;
        }
    }

    //Copy loop-back:
    if ((i = getEntry(routes, routes->name)) >= 0) {
        bzero(routes->route[i].dest, sizeof (routes->route[i].dest));
        strncpy(routes->route[i].dest, routes->name, strlen(routes->name));
        routes->route[i].cost = 0;
        routes->route[i].destPort = 0;
        routes->route[i].srcPort = 0;
    } else {
        return -1;
    }

    int j, k;
    for (i = 0; i < srcLsp->neighborCount; i++) {
        struct Node *neighbor = getNeighbor(srcLsp, i);
        if (j = getEntry(routes, neighbor->name) >= 0) {
            routes->route[j].cost = neighbor->cost;
            routes->route[j].destPort = neighbor->destPort;
            routes->route[j].srcPort = neighbor->srcPort;
        } else {
            return -1;
        }
    }
    return 0;
}

//Public
int dijkstrasEngine(struct RoutePool *routes, struct lspPool* lsps){
    int i = generateNodes(routes, lsps);
    if(i < 0){
        return -1;
    }
}