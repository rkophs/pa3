//
//  dynList_.h
//  PA3
//
//  Created by Ryan Kophs on 11/6/13.
//  Copyright (c) 2013 edu.kophs. All rights reserved.
//
#include "node_.h"

#define INTMAX 9999999
#define INTMEM 8

struct LSP {
    char sourceName[32];
    int seqNum;
    int timeToLive;
    struct Node *neighbors;
    int neighborCount;
};

struct LSP *createLSP(char *name, int nameLength, int timeToLive) {
    struct LSP *tmp;

    //Memory allocation:
    if ((tmp = (struct LSP *) malloc(sizeof (struct LSP))) == NULL) {
        return NULL; //Not enough memory
    }

    //Setting initiative #s:
    if (nameLength < sizeof (tmp->sourceName)) { //Prevent buffer overflows
        strncpy(tmp->sourceName, name, nameLength);
    } else {
        free(tmp);
        return NULL;
    }

    if ((tmp->neighbors = initList()) == NULL) {
        free(tmp); //Not enough memory
        return NULL;
    }

    tmp->seqNum = 0;
    tmp->timeToLive = timeToLive;
    tmp->neighborCount = 0;

    return tmp;
}

int addNeighbor(struct LSP *target, int cost, char *name, int nameLength) {
    if (target == NULL) {
        return -1;
    }

    int status;
    if ((status = appendNode(target->neighbors, cost, name, nameLength)) < 0) {
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

void emptyNeighbors(struct LSP *target){
    emptyList(target->neighbors);
    target->neighborCount = 0;
}

void removeLSP(struct LSP *target) {
    if (target == NULL) {
        return;
    }
    if (target->neighbors != NULL) {
        deleteList(target->neighbors);
    }

    free(target);
    target = NULL;
}

int cmpLSPs(struct LSP *a, struct LSP *b) {
    return a->seqNum - b->seqNum; //0 for equal, + for A > B, - for A < B
}

void incSeqNum(struct LSP *a) {
    a->seqNum++;
}

int printLSP(struct LSP *lsp, char *buff, int size) {

    int nStrS = 100;
    if (lsp == NULL) { //Must be valid LSP
        return -1;
    }

    bzero(buff, size);
    if ((strlen(lsp->sourceName) + 3 * (COSTMEM - 1) + nStrS + 8) >= size) {
        return -1; //Not enough buffer to continue
    }

    strcat(buff, "[");
    strncat(buff, lsp->sourceName, strlen(lsp->sourceName));
    strcat(buff, ",");
    
    char intStr[INTMEM];
    memset(intStr, ' ', INTMEM);
    insertNum(intStr, INTMAX, lsp->seqNum, INTMEM - 2);
    strncat(buff, intStr, INTMEM - 1);
    strcat(buff, ",");
    
    memset(intStr, ' ', INTMEM);
    insertNum(intStr, INTMAX, lsp->timeToLive, INTMEM - 2);
    strncat(buff, intStr, INTMEM - 1);
    strcat(buff, ",");
    
    memset(intStr, ' ', INTMEM);
    insertNum(intStr, INTMAX, lsp->neighborCount, INTMEM - 2);
    strncat(buff, intStr, INTMEM - 1);
    strcat(buff, ",");
    
    strcat(buff, "{");
    char nodes[nStrS];
    printAllNodes(lsp->neighbors ,nodes, nStrS);
    strcat(buff, nodes);
    strcat(buff, "}]");

    buff[size - 1] = 0;    
    return 0;
}