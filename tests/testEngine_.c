
#include "../dependencies/engine_.h"

int main(int argc, char** argv) {

    int buffSize = 1024;
    char buff[buffSize];
    

    printf("Init router A:\n");
    struct LSP *router = createLSP("A", 1, 100, 0);
    addNeighbor(router, 4, "B", 1, 9701, 9704);
    addNeighbor(router, 1, "C", 1, 9702, 9706);
    addNeighbor(router, 4, "F", 1, 9703, 9717);
    struct Engine *engine = initEngine(router, NULL);

    printf("Adding first LSP:\n");
    struct LSP *n0 = createLSP("A", 1, 100, 0);
    addNeighbor(n0, 4, "B", 1, 9701, 9704);
    addNeighbor(n0, 1, "C", 1, 9702, 9706);
    addNeighbor(n0, 4, "F", 1, 9703, 9717);
    engineProcessLSP(engine, n0);

    bzero(buff, buffSize);
    BuffRouteTable(engine->routes, buff, buffSize);
    printf("%s\n", buff);

    printf("Adding next LSPs:\n");
    n0 = createLSP("B", 1, 11, 5);
    addNeighbor(n0, 4, "A", 1, 9704, 9701);
    addNeighbor(n0, 1, "D", 1, 9705, 9709);
    engineProcessLSP(engine, n0);

    n0 = createLSP("C", 1, 11, 5);
    addNeighbor(n0, 1, "A", 1, 9706, 9702);
    addNeighbor(n0, 1, "D", 1, 9707, 9710);
    addNeighbor(n0, 3, "E", 1, 9708, 9713);
    engineProcessLSP(engine, n0);

    n0 = createLSP("D", 1, 13, 5);
    addNeighbor(n0, 1, "B", 1, 9709, 9705);
    addNeighbor(n0, 1, "C", 1, 9710, 9707);
    addNeighbor(n0, 1, "E", 1, 9711, 9714);
    addNeighbor(n0, 2, "F", 1, 9712, 9718);
    engineProcessLSP(engine, n0);

    n0 = createLSP("E", 1, 14, 6);
    addNeighbor(n0, 3, "C", 1, 9713, 9708);
    addNeighbor(n0, 1, "D", 1, 9714, 9711);
    addNeighbor(n0, 1, "F", 1, 9715, 9716);
    engineProcessLSP(engine, n0);

    n0 = createLSP("F", 1, 15, 4);
    addNeighbor(n0, 4, "A", 1, 9717, 9703);
    addNeighbor(n0, 2, "D", 1, 9718, 9712);
    addNeighbor(n0, 1, "E", 1, 9716, 9715);
    engineProcessLSP(engine, n0);

    printf("Final Routing table:\n");
    bzero(buff, buffSize);
    BuffRouteTable(engine->routes, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Changing connection between A and C:\n");
    n0 = createLSP("C", 1, 11, 6);
    addNeighbor(n0, 1, "A", 1, 9706, 9702);
    addNeighbor(n0, 10, "D", 1, 9707, 9710);
    addNeighbor(n0, 3, "E", 1, 9708, 9713);
    engineProcessLSP(engine, n0);
    n0 = createLSP("D", 1, 13, 5);
    addNeighbor(n0, 1, "B", 1, 9709, 9705);
    addNeighbor(n0, 10, "C", 1, 9710, 9707);
    addNeighbor(n0, 1, "E", 1, 9711, 9714);
    addNeighbor(n0, 2, "F", 1, 9712, 9718);
    engineProcessLSP(engine, n0);
    
    printf("Final Routing table:\n");
    bzero(buff, buffSize);
    BuffRouteTable(engine->routes, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Insert New LSP A with new data and hope it doesn't insert:\n");
    n0 = createLSP("A", 1, 1, 4);
    addNeighbor(n0, 4, "X", 1, 9717, 9703);
    addNeighbor(n0, 2, "Y", 1, 9718, 9712);
    addNeighbor(n0, 1, "Z", 1, 9716, 9715);
    engineProcessLSP(engine, n0);
    printf("Final Routing table:\n");
    bzero(buff, buffSize);
    BuffRouteTable(engine->routes, buff, buffSize);
    printf("%s\n", buff);

    n0 = createLSP("F", 1, 1, 1);
    addNeighbor(n0, 4, "X", 1, 9717, 9703);
    addNeighbor(n0, 2, "Y", 1, 9718, 9712);
    addNeighbor(n0, 1, "Z", 1, 9716, 9715);
    engineProcessLSP(engine, n0);
    
    releaseEngine(engine);
    engine = NULL;
    
    printf("new:------------------------\n");
    
    struct LSP *router3 = createLSP("A", 1, 100, 0);
    addNeighbor(router3, 4, "B", 1, 9701, 9704);
    addNeighbor(router3, 1, "C", 1, 9702, 9706);
    addNeighbor(router3, 4, "F", 1, 9703, 9717);
    struct Engine *engine3 = initEngine(router3, NULL);
    
    bzero(buff, buffSize);
    BuffAllLSPs(engine3->lsps, buff, buffSize);
    printf("%s\n", buff);
    
    struct LSP *router4 = createLSP("B", 1, 100, 0);
    addNeighbor(router4, 4, "B", 1, 9701, 9704);
    addNeighbor(router4, 1, "C", 1, 9702, 9706);
    addNeighbor(router4, 4, "F", 1, 9703, 9717);
    
    struct LSP *router5 = createLSP("C", 1, 100, 0);
    addNeighbor(router5, 4, "B", 1, 9701, 9704);
    addNeighbor(router5, 1, "C", 1, 9702, 9706);
    addNeighbor(router5, 4, "F", 1, 9703, 9717);
    
    engineProcessLSP(engine3, router4);
    engineProcessLSP(engine3, router5);
    
    bzero(buff, buffSize);
    BuffAllLSPs(engine3->lsps, buff, buffSize);
    printf("%s\n", buff);
    
    releaseEngine(engine3);

    return (EXIT_SUCCESS);
}

