#include "routePool_.h"
#include <ctype.h>

struct ARGS {
    char initFile[256];
    char logFile[256];
    char routerName[32];
    int destroyTime;
};

struct ARGS *initArgs(int argc, char **argv){
    if(argc < 4){
        return NULL;
    }
    
    struct ARGS *tmp;
    if((tmp = (struct ARGS *) malloc(sizeof(struct ARGS))) == NULL){
        return NULL;
    }
    
    if(argc == 5){
        tmp->destroyTime = atoi(argv[4]);
    } else {
        tmp->destroyTime = -1;
    }
    
    int rLen = strlen(argv[1]);
    int lLen = strlen(argv[2]);
    int iLen = strlen(argv[3]);
    
    if(rLen >= sizeof(tmp->routerName) 
            || lLen >= sizeof(tmp->logFile) 
            || iLen >= sizeof(tmp->initFile)){
        free(tmp);
        return NULL;
    }
    
    bzero(tmp->initFile, sizeof(tmp->initFile));
    bzero(tmp->logFile, sizeof(tmp->logFile));
    bzero(tmp->routerName, sizeof(tmp->routerName));
    
    strncpy(tmp->initFile, argv[3], iLen);
    strncpy(tmp->logFile, argv[2], lLen);
    strncpy(tmp->routerName, argv[1], rLen);
    
    return tmp;
}

struct LSP *parseInitFile(struct ARGS *args){
    int it, i;
    
    char name[32];
    char router[32];
    bzero(router, sizeof(router));
    bzero(name, sizeof(name));
    
    int src = 0;
    int dest = 0;
    int cost = 0;
    
    FILE *file;
    if (!(file = fopen(args->initFile, "rb"))) {
        return NULL;
    }
    
    struct LSP *lsp;
    lsp = NULL;
    
    char buff[4];
    bzero(buff, 4);
    do {
        bzero(buff, sizeof(buff));
        fread(buff, 1, 1, file);
        if(buff[0] == '<'){
            src = 0;
            dest = 0;
            cost = 0;
            it = 0;
            i = 0;
            bzero(name, sizeof(name));
        } else if(it == 0 && isalpha(buff[0])){ //Router Name
            router[i] = buff[0];
            i++;
        } else if(it == 1 && isdigit(buff[0])){ //SrcPort
            src *= 10;
            src += buff[0] - 48;
        } else if(it == 2 && isalpha(buff[0])){ //Router Name
            name[i] = buff[0];
            i++;
        } else if(it == 3 && isdigit(buff[0])){ //SrcPort
            dest *= 10;
            dest += buff[0] - 48;
        } else if(it == 4 && isdigit(buff[0])){ //SrcPort
            cost *= 10;
            cost += buff[0] - 48;
        } else if(buff[0] == ','){
            it++;
            i = 0;
        } else if(buff[0] == '>' && (!strcmp(router, args->routerName))){
            if(lsp == NULL){
                if((lsp = createLSP(args->routerName, strlen(router), 1000, 0)) == NULL){
                    fclose(file);
                    return NULL;
                }
                if(addNeighbor(lsp, cost, name, strlen(name), src, dest) < 0){
                    releaseLSP(lsp);
                    fclose(file);
                    return NULL;
                }
            } else {
                if(addNeighbor(lsp, cost, name, strlen(name), src, dest) < 0){
                    releaseLSP(lsp);
                    fclose(file);
                    
                    return NULL;
                }
                
            }
        }
    } while(buff[0]);
    fclose(file);
    return lsp;
}

struct LSP* parsePacket(char *buff, int buffSize, int *it, int *die){
    char tmp[4];
    bzero(tmp, 4);
    int node = -1;
    
    int lspIT = -1;
    int nodeIT = -1;
    struct LSP *lsp;
    
    char name[32];
    bzero(name, sizeof(name));
    char nodeName[32];
    bzero(nodeName, sizeof(nodeName));
    
    int ttl = 0;
    int seqNum = 0;
    int cost = 0;
    int srcPort = 0;
    int dstPort = 0;
    
    int i = 0;
    int eof = 0;
        
    do {
        eof++;
        bzero(tmp, sizeof(tmp));
        tmp[0] = buff[*it];
        (*it)++;
        if(tmp[0] == '['){ //Start of LSP
            lspIT = 0;
            i = 0;
        } else if (tmp[0] == ']'){
            i = 0;
            return lsp;
        } else if (tmp[0] == '<'){
            node = 1;
            nodeIT = 0;
            i = 0;
        } else if (tmp[0] == '>'){
            node = 0;
            i = 0;
            if(addNeighbor(lsp, cost, nodeName, strlen(nodeName), srcPort, dstPort) < 0){
                releaseLSP(lsp);
                return NULL;
            }
            bzero(nodeName, sizeof(nodeName));
            cost = 0;
            dstPort = 0;
            srcPort = 0;
            nodeIT = 0;
        } else if (tmp[0] == ',' && node != 1){ //LSP main part
            if(lspIT == 3){
                lsp = createLSP(name, strlen(name), ttl, seqNum);
                bzero(name, sizeof(name));
                ttl = 0;
                seqNum = 0;
            }
            lspIT++;
            i = 0;
        } else if (tmp[0] == ',' && node == 1){ //Inside node
            i = 0;
            nodeIT++;
        } else if (isalpha(tmp[0]) && lspIT == 0){
            name[i] = tmp[0];
            i++;
        } else if (isdigit(tmp[0]) && lspIT == 1){
            seqNum *= 10;
            seqNum += tmp[0] - 48;
        } else if (isdigit(tmp[0]) && lspIT == 2){
            ttl *= 10;
            ttl += tmp[0] - 48;
        } else if (isalpha(tmp[0]) && node == 1 && nodeIT == 0){ //node name
            nodeName[i] = tmp[0];
            i++;
        } else if (isdigit(tmp[0]) && node == 1 && nodeIT == 1){ //node cost
            cost *= 10;
            cost += tmp[0] - 48;
        } else if (isdigit(tmp[0]) && node == 1 && nodeIT == 2){
            srcPort *= 10;
            srcPort += tmp[0] - 48;
        } else if (isdigit(tmp[0]) && node == 1 && nodeIT == 3){
            dstPort *= 10;
            dstPort += tmp[0] - 48;
        } else if (tmp[0] == '*') {
            *die = 1;
            return NULL;
        }
    } while (tmp[0] != 0 && eof <= buffSize);
    releaseLSP(lsp);
    return NULL;
}

