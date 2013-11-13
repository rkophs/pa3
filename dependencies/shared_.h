
#include <stdarg.h>

#include "engine_.h"

void insertNum(char * buffer, int buffSize, int num, int leastSignificantPos){
    if(num == 0){
        buffer[leastSignificantPos] = '0';
        return;
    }
    if(num < 0 || num > buffSize){
        buffer[leastSignificantPos] = '1';
        buffer[leastSignificantPos - 1] = '-';
        return;
    }
    int tmp = num;
    int i = leastSignificantPos;
    while(tmp){
        buffer[i] = tmp % 10 + 48;
        tmp /= 10;
        i--;
    }
}

int LOG(FILE *file, const char *format, ...) {
    char buffer[1024];
    bzero(buffer, 1024);
    va_list args;
    va_start(args, format);
    int size = vsprintf(buffer, format, args);

    if (fwrite(buffer, 1, size, file) != size) {
        return -1;
    }
    va_end(args);
    return 0;
}

int BUFF(char *buffer, int size, const char *format, ...) {
    va_list args;
    va_start(args, format);
    bzero(buffer, size);
    int sizeUlt = vsprintf(buffer, format, args);
    va_end(args);
    return sizeUlt;
}

int LogAllNodes(struct Node *target, FILE* file){
    if(target == NULL || target->cost != -2){ //Must be valid list header
        return -1;
    }
    
    struct Node *it;
    it = target->next;

    while(it != NULL){
        LOG(file, "< ID: %s , Cost: %i , SrcPort: %i , DestPort: %i >", 
                it->name, it->cost, it->srcPort, it->destPort);
        it = it->next;
    }
    return 0;
}

int BuffAllNodes(struct Node *target, char *buff, int size){
    if(target == NULL || target->cost != -2){ //Must be valid list header
        return -1;
    }

    bzero(buff, size);
    struct Node *it;
    it = target->next;
    int i = 0;
    while(it != NULL){
        char temp[size];
        bzero(temp, size);
        int ultSize = BUFF(temp, size, "< ID: %s , Cost: %i , SrcPort: %i , DestPort: %i >", 
                it->name, it->cost, it->srcPort, it->destPort);
        strncat(buff, temp, ultSize);
        it = it->next;
    }
    
    buff[size-1] = 0;
    return 0;
}

int BuffLSP(struct LSP *lsp, char *buff, int size) {
    if (lsp == NULL) { //Must be valid LSP
        return -1;
    }
    int nStrS = lsp->neighborCount * MAXNODE + 1;

    bzero(buff, size);
    char nodes[nStrS];
    bzero(nodes, nStrS);
    if(lsp->neighborCount > 0){
        BuffAllNodes(lsp->neighbors, nodes, nStrS);
    }
    BUFF(buff, size, "[%s , %i , %i , %i , {%s}]", lsp->sourceName, lsp->seqNum, 
            lsp->timeToLive, lsp->neighborCount, nodes);
    buff[size - 1] = 0;
    return 0;
}

int BuffAllLSPs(struct lspPool *pool, char *buff, int size){
    struct LSP *target = pool->lsps;
    bzero(buff, size);
    
    struct LSP *it = target;
    strcat(buff, "{");
    while(it != NULL){
        char tmp[it->neighborCount*MAXNODE + 101];
        bzero(tmp, it->neighborCount*MAXNODE + 101);
        BuffLSP(it, tmp, it->neighborCount*MAXNODE + 101);
        strcat(buff, tmp);
        it = it->next;
    }
    strcat(buff, "}");
    return 0;
}

int BuffRouteTable(struct RoutePool *pool, char *buff, int size){
    if(pool == NULL){
        return -1;
    }
    
    bzero(buff, size);
    strncat(buff, "[", 1);
    int i;
    for(i = 0 ; i < pool->count; i++){
        char temp[size];
        bzero(temp, size);
        int ultSize = BUFF(temp, size,
                "< Dest: %s , Cost: %i , SrcPort: %i , DestPort: %i >", 
                pool->route[i].dest, pool->route[i].cost, 
                pool->route[i].srcPort, pool->route[i].destPort);
        strncat(buff, temp, ultSize);
    }
    strncat(buff, "]", 1);
    
    buff[size-1] = 0;
    return 0;
}

int LogRouteTable(struct RoutePool *pool, FILE *file){
    if(pool == NULL){
        return -1;
    }
    
    struct Route *it = pool->route;
    LOG(file, "----------------Routing Table--------------\n");
    int i;
    for(i = 0; i < pool->count; i++){
        LOG(file,"< Dest: %s , Cost: %i , SrcPort: %i , DestPort: %i >", 
                pool->route[i].dest, pool->route[i].cost, 
                pool->route[i].srcPort, pool->route[i].destPort);
        LOG(file, "\n");
    }
    LOG(file, "---------End of Routing Table--------------\n");
}


int LogLSP(struct LSP *lsp, FILE *file){
    if (lsp == NULL) { //Must be valid LSP
        return -1;
    }
    
    LOG(file, "[%s , %i , %i , %i , {", lsp->sourceName, lsp->seqNum, 
            lsp->timeToLive, lsp->neighborCount);
    LogAllNodes(lsp->neighbors, file);
    LOG(file, "%s}]");
    
    return 0;
}

int LogAllLSPs(struct LSP* target, FILE *file){
    struct LSP *it = target;
    LOG(file, "----------------LSP Pool--------------\n");
    while(it != NULL){
        LogLSP(it, file);
        LOG(file, "\n");
    }
    LOG(file, "---------End of LSP Pool--------------\n");
}
