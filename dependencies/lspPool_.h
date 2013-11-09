
#include "LSP_.h"

struct lspPool {
    struct LSP *lsps;
};

struct lspPool *createLSPPool(){
    struct lspPool *tmp;
    if ((tmp = (struct lspPool *) malloc(sizeof (struct lspPool))) == NULL) {
        return NULL; //Not enough memory
    }
    return tmp;
}

//Returns 0 of shallow append is in fact performed;
int shallowAppendLSP(struct lspPool *pool, struct LSP *shallowCpy) {
    if (pool == NULL || shallowCpy == NULL) {
        return -1; //not valid
    }
    
    if(pool->lsps == NULL){
        pool->lsps = shallowCpy;
        return 0;
    }

    struct LSP *it = pool->lsps;
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

int delSingleLSP(struct lspPool *pool, char *name){
    if(pool == NULL){
        return -1;
    }
    
    
    if(!strcmp(pool->lsps->sourceName, name)){ //First node remove
        struct LSP *tmp = pool->lsps;
        pool->lsps = pool->lsps->next;
        releaseLSP(tmp);
        return 0;
    }
    
    struct LSP *curr = pool->lsps->next;
    struct LSP *prev = pool->lsps;
    
    while(curr != NULL){
        if(!strcmp(curr->sourceName, name)){
            struct LSP *tmp = curr->next;
            releaseLSP(curr);
            prev->next = tmp;
            return 0;
        }
        curr = curr->next;
        prev = prev->next;
    }
    return -1;
}

int CmpSwapSingleLSP(struct lspPool *pool, struct LSP *swap){
    if(pool == NULL || swap == NULL){
        return -1; //invalid
    }
    
    struct LSP *lsp = pool->lsps;
    if((!strcmp(lsp->sourceName, swap->sourceName)) && swap->seqNum < lsp->seqNum){
        //Match: The sourceNames match, indicating same packet, and the swap seq # is lower
        struct LSP* tmp = lsp->next;
        releaseLSP(lsp);
        pool->lsps = swap;
        swap->next = tmp;
        return 0;
    }
    
    struct LSP* curr = lsp->next;
    struct LSP* prev = lsp;
    while(curr != NULL){
        if((!strcmp(curr->sourceName, swap->sourceName)) && swap->seqNum < curr->seqNum){
            //Match: The sourceNames match, indicating same packet, and the swap seq # is lower
            struct LSP* tmp = curr->next;
            releaseLSP(curr);
            prev->next = swap;
            swap->next = tmp;
            return 0;
        }
        curr = curr->next;
        prev = prev->next;
    }
    return -1;
}

void releaseAllLSPs(struct LSP *lsp){
    if(lsp == NULL){
        return;
    }
    
    struct LSP *it = lsp;
    struct LSP *tmp;
    
    while (it != NULL) {
        tmp = it->next;
        releaseLSP(it);
        it = tmp;
    }
    
    lsp = NULL;
}

void releaseLSPPool(struct lspPool *target){
    if(target == NULL){
        return;
    }
    releaseAllLSPs(target->lsps);
    free(target);
    target = NULL;
}

int lspPoolCtrl(struct lspPool *target, struct LSP *lsp){
    if(target == NULL || lsp == NULL){
        return -1; //Invalid entries
    }
    if(shallowAppendLSP(target, lsp) < 0 ){ //lsp seqName already exists
        if(CmpSwapSingleLSP(target, lsp) < 0){ //lsp exists w/ lower seq already
            releaseLSP(lsp); //Release this LSP because it is garbage
            return -1; //already in pool at a lower number
        }
        return 2; //Updated LSP with lower Seq#;
    }
    return 1; //New LSP of unknown router name is added
}
