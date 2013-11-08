/* 
 * File:   testNode_.c
 * Author: ryan
 *
 * Created on November 7, 2013, 2:42 PM
 */
#include "../dependencies/shared_.h"

int main(int argc, char** argv) {
    int buffSize = 2048;
    char buff[buffSize];
    struct Node *n1;
    if((n1 = initList()) == NULL){
        printf("Not enough memory!\n");
        return -1;
    }
    
    
    appendNode(n1, 0, "A", 1);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    emptyList(n1);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    appendNode(n1, 0, "AA", 2);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    appendNode(n1, 5, "B", 1);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    emptyList(n1);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    appendNode(n1, 0, "AAA", 3);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    appendNode(n1, 5, "BB", 2);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    appendNode(n1, 6, "C", 1);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    emptyList(n1);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    appendNode(n1, 0, "KOPHS", 5);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    appendNode(n1, 10, "TESTS", 5);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    appendNode(n1, 234, "THESE", 15);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    deleteNode(n1, "THESE");
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    deleteNode(n1, "KOPHSS");
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    deleteNode(n1, "KOPHS");
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    deleteNode(n1, "ABCD");
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    deleteNode(n1, "TESTS");
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    appendNode(n1, 23, "a1", 2);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    appendNode(n1, 10, "a2", 2);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    appendNode(n1, 234, "a3", 2);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);

    appendNode(n1, 0, "a4", 2);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    appendNode(n1, 10, "a5", 2);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    appendNode(n1, 234, "a6", 2);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    deleteNode(n1, "TESTS");
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    deleteNode(n1, "a5");
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    deleteNode(n1, "a3");
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    appendNode(n1, 234, "a7", 2);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    appendNode(n1, 234, "a7", 2);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    appendNode(n1, 234, "a1", 2);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    appendNode(n1, 234, "a3", 2);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    deleteNode(n1, "a1");
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    deleteNode(n1, "a2");
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    appendNode(n1, 234, "a8", 2);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    deleteList(n1);
    
    return 0;
}