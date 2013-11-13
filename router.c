#include "dependencies/shared_.h"

int main(int argc, char **argv){

    struct Engine* engine = startEngine(argc, argv);

    
    

    releaseEngine(engine);
    return 0;
}