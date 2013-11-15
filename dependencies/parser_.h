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
