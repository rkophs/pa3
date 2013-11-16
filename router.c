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
    
    engineRun(engine);
    printf("Router: %s is closing...\n", engine->args->routerName);

    releaseEngine(engine);
    return 0;
}