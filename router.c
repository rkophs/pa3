#include "dependencies/engine_.h"

int main(int argc, char **argv) {
    
    struct Engine* engine;
    if((engine = startEngine(argc, argv)) == NULL){
        return -1;
    }

    if(engineSyncRouters(engine) < 0){
        releaseEngine(engine);
        return -1;
    }
    
    printf("Starting the run\n");
    engineRun(engine);
    
    int buffSize = 2048;
    char buff[buffSize];
    bzero(buff, buffSize);
    BuffRouteTable(engine->routes, buff, buffSize);
    printf("Table: %s\n", buff);

    releaseEngine(engine);
    return 0;
}