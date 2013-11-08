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
    struct LSP *next;
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
    tmp->next = NULL;

    return tmp;
}

int shallowAppendLSP(struct LSP *lsp, struct LSP *shallowCpy) {
    if (lsp == NULL || shallowCpy == NULL) {
        return -1; //not valid
    }

    struct LSP *it;
    it = lsp;
    while (it->next != NULL) {
        if (!strcmp(it->sourceName, shallowCpy->sourceName)) {
            //already exists in the list of LSPs
            return -1;
        }
        it = it->next;
    }
    if (!strcmp(it->sourceName, shallowCpy->sourceName)) {
        return -1;
    }
    it->next = shallowCpy;
    return 0;
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

int delSingleLSP(struct LSP *lsp, char *name){
    if(lsp == NULL){
        return 1;
    }
    
    if(!strcmp(lsp->sourceName, name)){ //First node remove
        struct LSP *tmp = lsp->next;
        removeLSP(lsp);
        lsp = tmp;
        return;
    }
    
    struct LSP *curr = lsp->next;
    struct LSP *prev = lsp;
    
    while(curr != NULL){
        if(!strcmp(curr->sourceName, name)){
            struct LSP *tmp = curr->next;
            removeLSP(curr);
            prev->next = tmp;
            return 0;
        }
        curr = curr->next;
        prev = prev->next;
    }
    return -1;
}

int CmpSwapSingleLSP(struct LSP *lsp, struct LSP *swap){
    if(lsp == NULL || swap == NULL){
        return -1; //invalid
    }
    if((!strcmp(lsp->sourceName, swap->sourceName)) && swap->seqNum < lsp->seqNum){
        //Match: The sourceNames match, indicating same packet, and the swap seq # is lower
        free(lsp);
        lsp = swap;    
    }
    
    struct LSP* curr = lsp->next;
    struct LSP* prev = lsp;
    while(curr != NULL){
        if((!strcmp(curr->sourceName, swap->sourceName)) && swap->seqNum < curr->seqNum){
            //Match: The sourceNames match, indicating same packet, and the swap seq # is lower
            struct LSP* tmp = curr->next;
            removeLSP(curr);
            prev->next = swap;
            swap->next = tmp;
            return 0;
        }
    }
    return -1;
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

void emptyNeighbors(struct LSP *target) {
    emptyList(target->neighbors);
    target->neighborCount = 0;
}

void removeAllLSPs(struct LSP *lsp){
    if(lsp == NULL){
        return;
    }
    
    struct LSP *it = lsp;
    struct LSP *tmp;
    
    while (it != NULL) {
        tmp = it->next;
        removeLSP(it);
        it = tmp;
    }
    
    lsp = NULL;
}

int cmpLSPs(struct LSP *a, struct LSP *b) {
    return a->seqNum - b->seqNum; //0 for equal, + for A > B, - for A < B
}

void incSeqNum(struct LSP *a) {
    a->seqNum++;
}