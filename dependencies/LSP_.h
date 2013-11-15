#include "node_.h"

#define INTMAX 9999999
#define INTMEM 8

struct LSP {
    char sourceName[32];
    int timeToLive;
    int seqNum;
    struct Node *neighbors;
    int neighborCount;
    struct LSP *next;
};

struct LSP *createLSP(char *name, int nameLength, int timeToLive, int seqNum) {
    struct LSP *tmp;

    //Memory allocation:
    if ((tmp = (struct LSP *) malloc(sizeof (struct LSP))) == NULL) {
        return NULL; //Not enough memory
    }

    //Setting initiative #s:
    if (nameLength < sizeof (tmp->sourceName)) { //Prevent buffer overflows
        bzero(tmp->sourceName, sizeof(tmp->sourceName));
        strncpy(tmp->sourceName, name, nameLength);
    } else {
        free(tmp);
        return NULL;
    }

    if ((tmp->neighbors = initList()) == NULL) {
        free(tmp); //Not enough memory
        return NULL;
    }

    tmp->seqNum = seqNum;
    tmp->timeToLive = timeToLive;
    tmp->neighborCount = 0;
    tmp->next = NULL;

    return tmp;
}

//private:
void releaseLSP(struct LSP *target) {
    if (target == NULL) {
        return;
    }
    if (target->neighbors != NULL) {
        deleteList(target->neighbors);
    }
    free(target);
    target = NULL;
}

int addNeighbor(struct LSP *target, int cost, char *name, int nameLength, int srcPort, int destPort) {
    if (target == NULL) {
        return -1;
    }

    int status;
    if ((status = appendNode(target->neighbors, cost, name, nameLength, srcPort, destPort)) < 0) {
        return -1;
    }
    target->neighborCount++;
    return 0;
}

int delNeighbor(struct LSP *target, char *name) {
    if (target == NULL) {
        return -1;
    }

    int status;
    if ((status = deleteNode(target->neighbors, name)) < 0) {
        return -1;
    }
    target->neighborCount--;
    return 0;
}

struct Node *getNeighborByIt(struct LSP *target, int it){
    if(target == NULL || target->neighbors == NULL){
        return NULL;
    }
    
    int i = 1;
    struct Node *tmp = target->neighbors->next;
    while(i <= it && tmp != NULL){
        tmp = tmp->next;
        i++;
    }
    return tmp;
}

int getTTL(struct LSP *target){
    if(target == NULL){
        return -1;
    }
    return target->timeToLive;
}

int decrementTTL(struct LSP *target){
    if(target == NULL){
        return -1;
    }
    target->timeToLive--;
    return 0;
}

void emptyNeighbors(struct LSP *target) {
    emptyList(target->neighbors);
    target->neighborCount = 0;
}

void incSeqNum(struct LSP *a) {
    a->seqNum++;
}

int cmpLSPs(struct LSP *a, struct LSP *b) {
    return a->seqNum - b->seqNum; //0 for equal, + for A > B, - for A < B
}