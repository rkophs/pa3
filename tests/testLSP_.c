
#include "../dependencies/shared_.h"

int main(int argc, char** argv) {

    struct LSP *n1;
    int buffSize = 2048;
    char buff[buffSize];
    
    if((n1 = createLSP("A", 1, 10, 0)) == NULL){
        return -1; //error
    }
    
    printf("Adding A\n");
    addNeighbor(n1, 0, "A", 1, 12, 12);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("empty:\n");
    emptyNeighbors(n1);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Adding AA\n");
    addNeighbor(n1, 0, "AA", 2, 12, 12);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Adding B\n");
    addNeighbor(n1, 5, "B", 1, 12, 12);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("empty\n");
    emptyNeighbors(n1);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Adding AAA\n");
    addNeighbor(n1, 0, "AAA", 3, 12, 12);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Adding BB\n");
    addNeighbor(n1, 5, "BB", 2, 12, 12);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Adding C\n");
    addNeighbor(n1, 6, "C", 1, 12, 12);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("empty\n");
    emptyNeighbors(n1);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Adding KOPHS\n");
    addNeighbor(n1, 0, "KOPHS", 5, 12, 12);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Adding TESTS\n");
    addNeighbor(n1, 10, "TESTS", 5, 12, 12);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Adding THESE\n");
    addNeighbor(n1, 234, "THESE", 15, 12, 12);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Get 0");
    struct Node *a0 = getNeighborByIt(n1, 0);
    printf(": %s\n", a0->name);
    
    printf("Get 1");
    struct Node *a1 = getNeighborByIt(n1, 1);
    printf(": %s\n", a1->name);
    
    printf("Get 2");
    struct Node *a2 = getNeighborByIt(n1, 2);
    printf(": %s\n", a2->name);
    
    printf("Get 3");
    struct Node *a3 = getNeighborByIt(n1, 3);
    printf(": %s\n", a3->name);
    
    printf("Deleting THESE\n");
    delNeighbor(n1, "THESE");
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Deleting KOPHSS\n");
    delNeighbor(n1, "KOPHSS");
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Deleting KOPHS A\n");
    delNeighbor(n1, "KOPHS");
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Deleting ABCD\n");
    delNeighbor(n1, "ABCD");
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Deleting TESTS\n");
    delNeighbor(n1, "TESTS");
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Adding a1\n");
    addNeighbor(n1, 23, "a1", 2, 12, 12);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Adding a2\n");
    addNeighbor(n1, 10, "a2", 2, 12, 12);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Adding a3\n");
    addNeighbor(n1, 234, "a3", 2, 12, 12);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);

    printf("Adding a4\n");
    addNeighbor(n1, 0, "a4", 2, 12, 12);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Adding a5\n");
    addNeighbor(n1, 10, "a5", 2, 12, 12);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Adding a6\n");
    addNeighbor(n1, 234, "a6", 2, 12, 12);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Deleting TESTS\n");
    delNeighbor(n1, "TESTS");
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Deleting a5\n");
    delNeighbor(n1, "a5");
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Deleting a3\n");
    delNeighbor(n1, "a3");
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Adding a7\n");
    addNeighbor(n1, 234, "a7", 2, 12, 12);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Adding a7\n");
    addNeighbor(n1, 234, "a7", 2, 12, 12);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Adding a1\n");
    addNeighbor(n1, 234, "a1", 2, 12, 12);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Adding a3\n");
    addNeighbor(n1, 234, "a3", 2, 12, 12);
    bzero(buff, buffSize);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("releaseLSP\n");
    releaseLSP(n1);
    
    if((n1 = createLSP("A", 1, 10, 0)) == NULL){
        return -1; //error
    }
    
    struct LSP *n2;
    if((n2 = createLSP("B", 1, 10, 0)) == NULL){
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
    
    releaseLSP(n1);
    releaseLSP(n2);
    
    return 0;
}

