
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Route {
    char dest[32];
    int cost;
    int outPort;
    int destPort;
    struct Route *next;
};

struct RoutePool {
    struct Route *route;
};

struct Route *initRoute(char *dest, int destSize, int cost, int outPort, int destPort) {
    struct Route *tmp;
    printf("inside init route\n");
    if ((tmp = (struct Route *) malloc(sizeof (struct Route))) == NULL) {
        return NULL; //Not enough memory
    }
    tmp->cost = cost;
    tmp->outPort = outPort;
    tmp->destPort = destPort;

    bzero(tmp->dest, sizeof (tmp->dest));
    if (strlen(tmp->dest) < destSize) { //prevent buffer overflows
        strncpy(tmp->dest, dest, destSize);
    } else {
        free(tmp);
        return NULL; //potential Buffer overflow
    }
    tmp->next = NULL;
    return tmp;
}

struct RoutePool *initRoutePool() {
    struct RoutePool *tmp;
    if ((tmp = (struct RoutePool *) malloc(sizeof (struct RoutePool))) == NULL) {
        return NULL;
    }
    tmp->route = NULL;
    return tmp;
}

int overrideAppendRoute(struct RoutePool *pool, struct Route *route) {
    if(pool == NULL || route == NULL){
        return -1;
    }
    
    if(pool->route == NULL){
        pool->route = route;
        return 0;
    }
    
    struct Route *curr = pool->route;
    struct Route *prev;
    
    if(!strcmp(curr->dest, route->dest)){ //Match in first position:
        struct Route *tmp = curr->next;
        free(curr);
        curr = NULL;
        pool->route = route;
        route->next = tmp;
        return 0;
    }
    prev = pool->route;
    curr = curr->next;
    
    while (curr != NULL) { //Iterate to end position
        if (!strcmp(curr->dest, route->dest)) {
            struct Route *tmp = curr->next;
            free(curr);
            curr = NULL;
            prev->next = route;
            route->next = tmp;
            return 0; //already exists;
        }
        curr = curr->next;
        prev = prev->next;
    }
    
    prev->next = route;
    return 0;
}

void releaseAllRoutes(struct RoutePool *pool) {
    if (pool == NULL) { //Not a header
        return;
    }

    struct Route *it = pool->route;
    struct Route *tmp;

    while (it != NULL) {
        tmp = it->next;
        free(it);
        it = tmp;
    }
    pool->route = NULL;
}

void releaseRoutePool(struct RoutePool *pool){
    if(pool == NULL){
        return;
    }
    
    releaseAllRoutes(pool);
    free(pool);
    pool = NULL;
}