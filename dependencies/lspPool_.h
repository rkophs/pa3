#include "LSP_.h"

struct lspPool {
    struct LSP *lsps;
    int count;
};

struct lspPool *createLSPPool(){
    struct lspPool *tmp;
    if ((tmp = (struct lspPool *) malloc(sizeof (struct lspPool))) == NULL) {
        return NULL; //Not enough memory
    }
    tmp->lsps = NULL;
    tmp->count = 0;
    return tmp;
}

//Returns 0 of shallow append is in fact performed;
int shallowAppendLSP(struct lspPool *pool, struct LSP *shallowCpy) {
    if (pool == NULL || shallowCpy == NULL) {
        return -1; //not valid
    }
    
    if(pool->lsps == NULL){
        pool->lsps = shallowCpy;
        pool->count++;
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
    pool->count++;
    return 0;
}

int CmpSwapSingleLSP(struct lspPool *pool, struct LSP *swap){
    if(pool == NULL || swap == NULL){
        return -1; //invalid
    }
    
    struct LSP *lsp = pool->lsps;
    if((!strcmp(lsp->sourceName, swap->sourceName)) && swap->seqNum > lsp->seqNum){
        //Match: The sourceNames match, indicating same packet, and the swap seq # is higher
        struct LSP* tmp = lsp->next;
        releaseLSP(lsp);
        pool->lsps = swap;
        swap->next = tmp;
        return 0;
    }
    
    struct LSP* curr = lsp->next;
    struct LSP* prev = lsp;
    while(curr != NULL){
        if((!strcmp(curr->sourceName, swap->sourceName)) && swap->seqNum > curr->seqNum){
            //Match: The sourceNames match, indicating same packet, and the swap seq # is higher
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

struct LSP *getLSPByName(struct lspPool *pool, char *src){
    if(pool == NULL){
        return NULL;
    }
    struct LSP *it = pool->lsps;
    while(it != NULL){
        if(!strcmp(it->sourceName, src)){
            //match:
            return it;
        }
        it = it->next;
    }
    return NULL;
}

struct LSP *getLSPByIt(struct lspPool *pool, int num){
    if(pool == NULL || pool->count <= num){
        return NULL;
    }
    struct LSP *it = pool->lsps;
    int i;
    for(i = 1; i <= num && i < pool->count; i++ ){
        it = it->next;
    }
    return it;
}

int delSingleLSP(struct lspPool *pool, char *name){
    if(pool == NULL){
        return -1;
    }
    
    
    if(!strcmp(pool->lsps->sourceName, name)){ //First node remove
        struct LSP *tmp = pool->lsps;
        pool->lsps = pool->lsps->next;
        releaseLSP(tmp);
        pool->count--;
        return 0;
    }
    
    struct LSP *curr = pool->lsps->next;
    struct LSP *prev = pool->lsps;
    
    while(curr != NULL){
        if(!strcmp(curr->sourceName, name)){
            struct LSP *tmp = curr->next;
            releaseLSP(curr);
            prev->next = tmp;
            pool->count++;
            return 0;
        }
        curr = curr->next;
        prev = prev->next;
    }
    return -1;
}

void releaseAllLSPs(struct lspPool *pool){
    if(pool == NULL){
        return;
    }
    
    struct LSP *it = pool->lsps;
    struct LSP *tmp;
    
    while (it != NULL) {
        tmp = it->next;
        releaseLSP(it);
        it = tmp;
    }
    pool->count = 0;
    pool->lsps = NULL;
}

void releaseLSPPool(struct lspPool *target){
    if(target == NULL){
        return;
    }
    releaseAllLSPs(target);
    target->count = 0;
    free(target);
    target = NULL;
}

/* 
 *              -1: Invalid, error occurred
 *               0: LSP already exists in pool at higher Seq#, dropped LSP
 *               1: Existing did not exist, LSP was successfully added
 *               2: Existing LSP was updated with new LSP of higher Seq#
 *               3: TTL of input is 0, corresponding LSP in pool was deleted
 *               4: TTL of input is 0, no corresponding LSP, stop transmit of 0
 */
int lspPoolCtrl(struct lspPool *target, struct LSP *lsp){
    if(target == NULL || lsp == NULL){
        releaseLSP(lsp);
        return -1; //Invalid entries
    }
    
//    if(getTTL(lsp) == 0){ //Time to live is 0:
//        int stat = delSingleLSP(target, lsp->sourceName);
//        if(stat == -1){ //Nothing was deleted, so it didn't exist to begin
//            releaseLSP(lsp); //Do not need to retransmit;
//            return 4;
//        }
//        return 3; //Something was deleted, retransmission will be needed
//    } else {
//        decrementTTL(lsp);
//    }
//    
    if(shallowAppendLSP(target, lsp) < 0 ){ //lsp seqName already exists
        if(CmpSwapSingleLSP(target, lsp) < 0){ //lsp exists w/ higher seq already
            releaseLSP(lsp); //Release this LSP because it is garbage
            return 0; //already in pool at a higher number
        }
        return 2; //Updated LSP with higher Seq#;
    }
    return 1; //New LSP of unknown router name is added
}
