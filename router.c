#include "dependencies/shared_.h"

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

    releaseEngine(engine);
    return 0;
}