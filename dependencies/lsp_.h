//
//  dynList_.h
//  PA3
//
//  Created by Ryan Kophs on 11/6/13.
//  Copyright (c) 2013 edu.kophs. All rights reserved.
//
#include <stdlib.h>
#include <string.h>
#include "node_.h"

struct LSP {
    char sourceName[32];
    int seqNum;
    int timeToLive;
    struct Node *neighbors;
    int neighborCount;
};

struct LSP *createLSP(char *name, int nameLength, int timeToLive){
    struct LSP *tmp;
    
    //Memory allocation:
    if ((tmp = (struct LSP *) malloc(sizeof(struct LSP))) == NULL ) {
        return NULL; //Not enough memory
    }
    
    //Setting initiative #s:
    if(nameLength < sizeof(tmp->sourceName)){ //Prevent buffer overflows
        strncpy(tmp->sourceName, name, nameLength);
    } else {
        free(tmp);
        return NULL;
    }
    
    if((tmp->neighbors = initList()) == NULL ){
        free(tmp); //Not enough memory
        return NULL;
    }
    
    tmp->seqNum = 0;
    tmp->timeToLive = timeToLive;
    tmp->neighborCount = 0;

    return tmp;
}

int addNeighbor(struct LSP *target, char *name, int nameLength, int cost){
    if(target == NULL){
        return -1;
    }
    
    int status;
    if((status = appendNode(target->neighbors, cost, name, nameLength)) < 0){
        return -1;
    }
    target->neighborCount++;
    return 0;
}

int delNeighbor(struct LSP *target, char *name){
    if(target == NULL){
        return -1;
    }
    
    int status;
    if ((status = deleteNode(target->neighbors, name)) < 0) {
        return -1;
    }
    target->neighborCount--;
    return 0;
}

void removeLSP(struct LSP *target){
    if (target == NULL) {
        return;
    }
    if (target->neighbors != NULL) {
        deleteList(target->neighbors);
    }
    
    free(target);
}

int cmpLSPs(struct LSP *a, struct LSP *b){
    return a->seqNum - b->seqNum; //0 for equal, + for A > B, - for A < B
}

void incSeqNum(struct LSP *a){
    a->seqNum++;
}
