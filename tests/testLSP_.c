/* 
 * File:   testLSP_.c
 * Author: ryan
 *
 * Created on November 7, 2013, 4:38 PM
 */

#include "../dependencies/shared_.h"

/*
 * 
 */
int main(int argc, char** argv) {

    struct LSP *n1;
    int buffSize = 2048;
    char buff[buffSize];
    
    if((n1 = createLSP("A", 1, 10)) == NULL){
        return -1; //error
    }
    
    addNeighbor(n1, 0, "A", 1);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    emptyNeighbors(n1);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    addNeighbor(n1, 0, "AA", 2);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    addNeighbor(n1, 5, "B", 1);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    emptyNeighbors(n1);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    addNeighbor(n1, 0, "AAA", 3);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    addNeighbor(n1, 5, "BB", 2);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    addNeighbor(n1, 6, "C", 1);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    emptyNeighbors(n1);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    addNeighbor(n1, 0, "KOPHS", 5);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    addNeighbor(n1, 10, "TESTS", 5);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    addNeighbor(n1, 234, "THESE", 15);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    delNeighbor(n1, "THESE");
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    delNeighbor(n1, "KOPHSS");
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    delNeighbor(n1, "KOPHS");
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    delNeighbor(n1, "ABCD");
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    delNeighbor(n1, "TESTS");
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    addNeighbor(n1, 23, "a1", 2);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    addNeighbor(n1, 10, "a2", 2);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    addNeighbor(n1, 234, "a3", 2);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);

    addNeighbor(n1, 0, "a4", 2);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    addNeighbor(n1, 10, "a5", 2);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    addNeighbor(n1, 234, "a6", 2);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    delNeighbor(n1, "TESTS");
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    delNeighbor(n1, "a5");
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    delNeighbor(n1, "a3");
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    addNeighbor(n1, 234, "a7", 2);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    addNeighbor(n1, 234, "a7", 2);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    addNeighbor(n1, 234, "a1", 2);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    addNeighbor(n1, 234, "a3", 2);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    removeLSP(n1);
    
    if((n1 = createLSP("A", 1, 10)) == NULL){
        return -1; //error
    }
    
    struct LSP *n2;
    if((n2 = createLSP("B", 1, 10)) == NULL){
        return -1; //error
    }
    
    incSeqNum(n1);
    
    if(cmpLSPs(n1, n2) < 0){
        printf("A is less than B\n");
    } else if (cmpLSPs(n1, n2) == 0){
        printf("A is equal to B\n");
    } else {
        printf("A is greater than B\n");
    }
    
    incSeqNum(n2);
    
    if(cmpLSPs(n1, n2) < 0){
        printf("A is less than B\n");
    } else if (cmpLSPs(n1, n2) == 0){
        printf("A is equal to B\n");
    } else {
        printf("A is greater than B\n");
    }
    
    incSeqNum(n2);
    incSeqNum(n2);
    incSeqNum(n2);
    incSeqNum(n2);
    
    if(cmpLSPs(n1, n2) < 0){
        printf("A is less than B\n");
    } else if (cmpLSPs(n1, n2) == 0){
        printf("A is equal to B\n");
    } else {
        printf("A is greater than B\n");
    }
    
    removeLSP(n1);
    removeLSP(n2);
    
    return 0;
}

