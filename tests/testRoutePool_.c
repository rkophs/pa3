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
    
    int buffSize = 2048;
    char buff[buffSize];
    
    struct RoutePool *pool = initRoutePool();
    
    struct Route *r0 = initRoute("A",1,10,3456,6789);
    struct Route *r1 = initRoute("B",1,23,3426,6589);
    struct Route *r2 = initRoute("C",1,45,3356,6489);
    struct Route *r3 = initRoute("D",1,11,3426,6289);
    struct Route *r4 = initRoute("E",1,19,3451,6389);
    struct Route *r5 = initRoute("F",1,53,2456,6189);
    struct Route *r6 = initRoute("F",1,34,1236,2199);
    struct Route *r7 = initRoute("A",1,99,4566,9149);
    struct Route *r8 = initRoute("B",1,59,2896,6929);
    
    printf("adding r0\n");
    overrideAppendRoute(pool, r0);
    bzero(buff, buffSize);
    BuffRouteTable(pool, buff, buffSize);
    printf("%s\n", buff);
    
    printf("adding r1\n");
    overrideAppendRoute(pool, r1);
    bzero(buff, buffSize);
    BuffRouteTable(pool, buff, buffSize);
    printf("%s\n", buff);
    
    printf("adding r2\n");
    overrideAppendRoute(pool, r2);
    bzero(buff, buffSize);
    BuffRouteTable(pool, buff, buffSize);
    printf("%s\n", buff);
    
    printf("adding r3\n");
    overrideAppendRoute(pool, r3);
    bzero(buff, buffSize);
    BuffRouteTable(pool, buff, buffSize);
    printf("%s\n", buff);
    
    printf("adding r4\n");
    overrideAppendRoute(pool, r4);
    bzero(buff, buffSize);
    BuffRouteTable(pool, buff, buffSize);
    printf("%s\n", buff);
    
    printf("adding r5\n");
    overrideAppendRoute(pool, r5);
    bzero(buff, buffSize);
    BuffRouteTable(pool, buff, buffSize);
    printf("%s\n", buff);
    
    printf("adding r6\n");
    overrideAppendRoute(pool, r6);
    bzero(buff, buffSize);
    BuffRouteTable(pool, buff, buffSize);
    printf("%s\n", buff);
    
    printf("adding r7\n");
    overrideAppendRoute(pool, r7);
    bzero(buff, buffSize);
    BuffRouteTable(pool, buff, buffSize);
    printf("%s\n", buff);
    
    printf("adding r8\n");
    overrideAppendRoute(pool, r8);
    bzero(buff, buffSize);
    BuffRouteTable(pool, buff, buffSize);
    printf("%s\n", buff);
    
    releaseRoutePool(pool);
    
    return (EXIT_SUCCESS);
}

