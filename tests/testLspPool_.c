/* 
 * File:   testLspPool_.c
 * Author: ryan
 *
 * Created on November 7, 2013, 9:14 PM
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
    bzero(buff, buffSize);
    
    struct lspPool *n1;
    struct LSP *n2;
    struct LSP *n3;
    struct LSP *n4;
    struct LSP *n5;
    struct LSP *n6;
    
    n1 = createLSPPool();
    n2 = createLSP("B", 1, 11, 1);
    n3 = createLSP("C", 1, 12, 1);
    n4 = createLSP("D", 1, 13, 1);
    n5 = createLSP("E", 1, 14, 1);
    n6 = createLSP("F", 1, 15, 1);
    
    printf("Buff n1:\n");
    BuffAllLSPs(n1, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Append n2:\n");
    shallowAppendLSP(n1, n2);
    bzero(buff, buffSize);
    BuffAllLSPs(n1, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Append n3:\n");
    shallowAppendLSP(n1, n3);
    bzero(buff, buffSize);
    BuffAllLSPs(n1, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Append n4:\n");
    shallowAppendLSP(n1, n4);
    bzero(buff, buffSize);
    BuffAllLSPs(n1, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Append n5:\n");
    shallowAppendLSP(n1, n5);
    bzero(buff, buffSize);
    BuffAllLSPs(n1, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Append n4:\n");
    shallowAppendLSP(n1, n4);
    bzero(buff, buffSize);
    BuffAllLSPs(n1, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Append n5:\n");
    shallowAppendLSP(n1, n5);
    bzero(buff, buffSize);
    BuffAllLSPs(n1, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Append n2:\n");
    shallowAppendLSP(n1, n2);
    bzero(buff, buffSize);
    BuffAllLSPs(n1, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Delete B:\n");
    delSingleLSP(n1, "B");
    bzero(buff, buffSize);
    BuffAllLSPs(n1, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Delete C:\n");
    delSingleLSP(n1, "C");
    bzero(buff, buffSize);
    BuffAllLSPs(n1, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Delete A:\n");
    delSingleLSP(n1, "A");
    bzero(buff, buffSize);
    BuffAllLSPs(n1, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Delete G:\n");
    delSingleLSP(n1, "G");
    bzero(buff, buffSize);
    BuffAllLSPs(n1, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Delete E:\n");
    delSingleLSP(n1, "E");
    bzero(buff, buffSize);
    BuffAllLSPs(n1, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Delete D:\n");
    delSingleLSP(n1, "D");
    bzero(buff, buffSize);
    BuffAllLSPs(n1, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Append n6:\n");
    shallowAppendLSP(n1, n6);
    bzero(buff, buffSize);
    BuffAllLSPs(n1, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Delete All:\n");
    releaseLSPPool(n1);
    bzero(buff, buffSize);
    BuffAllLSPs(n1, buff, buffSize);
    printf("%s\n", buff);
    
    return (EXIT_SUCCESS);
}

