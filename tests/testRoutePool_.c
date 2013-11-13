/* 
 * File:   testRoute_.c
 * Author: ryan
 *
 * Created on November 8, 2013, 9:20 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "../dependencies/shared_.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
    
    struct lspPool *pool;
    int buffSize = 2048;
    char buff[buffSize];
    bzero(buff, buffSize);
    
    struct LSP *n1; struct LSP *n2; struct LSP *n3; struct LSP *n4; struct LSP *n5;
    struct LSP *n6; struct LSP *n7; struct LSP *n8; struct LSP *n9; struct LSP *na;
    
    pool = createLSPPool();
    n1 = createLSP("A", 1, 10, 5);
    addNeighbor(n1, 4, "B", 1, 9701, 9704);
    addNeighbor(n1, 1, "C", 1, 9702, 9706);
    addNeighbor(n1, 4, "F", 1, 9703, 9717);
    n2 = createLSP("B", 1, 11, 5);
    addNeighbor(n2, 4, "A", 1, 9704, 9701);
    addNeighbor(n2, 1, "D", 1, 9705, 9709);
    n3 = createLSP("C", 1, 12, 5);
    addNeighbor(n3, 1, "A", 1, 9706, 9702);
    addNeighbor(n3, 1, "D", 1, 9707, 9710);
    addNeighbor(n3, 3, "E", 1, 9708, 9713);
    n4 = createLSP("D", 1, 13, 5);
    addNeighbor(n4, 1, "B", 1, 9709, 9705);
    addNeighbor(n4, 1, "C", 1, 9710, 9707);
    addNeighbor(n4, 1, "E", 1, 9711, 9714);
    addNeighbor(n4, 2, "F", 1, 9712, 9718);
    n5 = createLSP("E", 1, 14, 6);
    addNeighbor(n5, 3, "C", 1, 9713, 9708);
    addNeighbor(n5, 1, "D", 1, 9714, 9711);
    addNeighbor(n5, 1, "F", 1, 9715, 9716);
    n6 = createLSP("F", 1, 15, 4);
    addNeighbor(n6, 4, "A", 1, 9717, 9703);
    addNeighbor(n6, 2, "D", 1, 9718, 9712);
    addNeighbor(n6, 1, "E", 1, 9716, 9715);
    
    lspPoolCtrl(pool, n1);
    lspPoolCtrl(pool, n2);
    lspPoolCtrl(pool, n3);
    lspPoolCtrl(pool, n4);
    lspPoolCtrl(pool, n5);
    lspPoolCtrl(pool, n6);
    bzero(buff, buffSize);
    BuffAllLSPs(pool, buff, buffSize);
    printf("%s\n", buff);
        
    printf("Executing Dijkstra's...\n");
    
    struct RoutePool *rA = initRoutePool("A", 1);
    struct RoutePool *rB = initRoutePool("B", 1);
    struct RoutePool *rC = initRoutePool("C", 1);
    struct RoutePool *rD = initRoutePool("D", 1);
    struct RoutePool *rE = initRoutePool("E", 1);
    struct RoutePool *rF = initRoutePool("F", 1);
    
    printf("Pool A\n");
    dijkstrasEngine(rA, pool);
    bzero(buff, buffSize);
    BuffRouteTable(rA, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Pool B\n");
    dijkstrasEngine(rB, pool);
    bzero(buff, buffSize);
    BuffRouteTable(rB, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Pool C\n");
    dijkstrasEngine(rC, pool);
    bzero(buff, buffSize);
    BuffRouteTable(rC, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Pool D\n");
    dijkstrasEngine(rD, pool);
    bzero(buff, buffSize);
    BuffRouteTable(rD, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Pool E\n");
    dijkstrasEngine(rE, pool);
    bzero(buff, buffSize);
    BuffRouteTable(rE, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Pool F\n");
    dijkstrasEngine(rF, pool);
    bzero(buff, buffSize);
    BuffRouteTable(rF, buff, buffSize);
    printf("%s\n", buff);
    
    releaseLSPPool(pool);
    
    //---------------------------------------------
    
    struct RoutePool *rG = initRoutePool("G", 1);
    struct RoutePool *rH = initRoutePool("H", 1);
    struct RoutePool *rI = initRoutePool("I", 1);
    struct RoutePool *rJ = initRoutePool("J", 1);
    
    pool = createLSPPool();
    n1 = createLSP("A", 1, 10, 5);
    addNeighbor(n1, 1, "B", 1, 1, 2);
    addNeighbor(n1, 3, "H", 1, 16, 15);
    addNeighbor(n1, 5, "I", 1, 17, 18);
    n2 = createLSP("B", 1, 11, 5);
    addNeighbor(n2, 1, "A", 1, 2, 1);
    addNeighbor(n2, 1, "C", 1, 3, 4);
    addNeighbor(n2, 3, "I", 1, 20, 19);
    n3 = createLSP("C", 1, 12, 5);
    addNeighbor(n3, 1, "B", 1, 4, 3);
    addNeighbor(n3, 1, "D", 1, 5, 6);
    n4 = createLSP("D", 1, 13, 5);
    addNeighbor(n4, 1, "C", 1, 6, 5);
    addNeighbor(n4, 1, "E", 1, 7, 8);
    n5 = createLSP("E", 1, 14, 6);
    addNeighbor(n5, 1, "D", 1, 8, 7);
    addNeighbor(n5, 1, "F", 1, 9, 10);
    n6 = createLSP("F", 1, 15, 4);
    addNeighbor(n6, 1, "E", 1, 10, 9);
    addNeighbor(n6, 1, "G", 1, 11, 12);
    addNeighbor(n6, 1, "J", 1, 23, 22);
    n7 = createLSP("G", 1, 15, 4);
    addNeighbor(n7, 1, "F", 1, 12, 11);
    addNeighbor(n7, 3, "H", 1, 13, 14);
    n8 = createLSP("H", 1, 15, 4);
    addNeighbor(n8, 3, "A", 1, 15, 16);
    addNeighbor(n8, 3, "G", 1, 14, 13);
    addNeighbor(n8, 1, "I", 1, 24, 25);
    n9 = createLSP("I", 1, 15, 4);
    addNeighbor(n9, 5, "A", 1, 18, 17);
    addNeighbor(n9, 3, "B", 1, 19, 20);
    addNeighbor(n9, 1, "H", 1, 25, 24);
    addNeighbor(n9, 10, "J", 1, 26, 21);
    na = createLSP("J", 1, 15, 4);
    addNeighbor(na, 1, "F", 1, 22, 23);
    addNeighbor(na, 10, "I", 1, 21, 26);
    
    lspPoolCtrl(pool, n1);
    lspPoolCtrl(pool, n2);
    lspPoolCtrl(pool, n3);
    lspPoolCtrl(pool, n4);
    lspPoolCtrl(pool, n5);
    lspPoolCtrl(pool, n6);
    lspPoolCtrl(pool, n7);
    lspPoolCtrl(pool, n8);
    lspPoolCtrl(pool, n9);
    lspPoolCtrl(pool, na);
    
    bzero(buff, buffSize);
    BuffAllLSPs(pool, buff, buffSize);
    printf("%s\n", buff);
        
    printf("Executing Dijkstra's...\n");
    
    printf("Pool A\n");
    dijkstrasEngine(rA, pool);
    bzero(buff, buffSize);
    BuffRouteTable(rA, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Pool B\n");
    dijkstrasEngine(rB, pool);
    bzero(buff, buffSize);
    BuffRouteTable(rB, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Pool C\n");
    dijkstrasEngine(rC, pool);
    bzero(buff, buffSize);
    BuffRouteTable(rC, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Pool D\n");
    dijkstrasEngine(rD, pool);
    bzero(buff, buffSize);
    BuffRouteTable(rD, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Pool E\n");
    dijkstrasEngine(rE, pool);
    bzero(buff, buffSize);
    BuffRouteTable(rE, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Pool F\n");
    dijkstrasEngine(rF, pool);
    bzero(buff, buffSize);
    BuffRouteTable(rF, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Pool G\n");
    dijkstrasEngine(rG, pool);
    bzero(buff, buffSize);
    BuffRouteTable(rG, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Pool H\n");
    dijkstrasEngine(rH, pool);
    bzero(buff, buffSize);
    BuffRouteTable(rH, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Pool I\n");
    dijkstrasEngine(rI, pool);
    bzero(buff, buffSize);
    BuffRouteTable(rI, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Pool J\n");
    dijkstrasEngine(rJ, pool);
    bzero(buff, buffSize);
    BuffRouteTable(rJ, buff, buffSize);
    printf("%s\n", buff);
    
    releaseRoutePool(rA);
    releaseRoutePool(rB);
    releaseRoutePool(rC);
    releaseRoutePool(rD);
    releaseRoutePool(rE);
    releaseRoutePool(rF);
    releaseRoutePool(rG);
    releaseRoutePool(rH);
    releaseRoutePool(rI);
    releaseRoutePool(rJ);
    
    releaseLSPPool(pool);
    
    return (EXIT_SUCCESS);
}

