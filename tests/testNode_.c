
#include "../dependencies/shared_.h"

int main(int argc, char** argv) {
    int buffSize = 2048;
    char buff[buffSize];
    struct Node *n1;
    if((n1 = initList()) == NULL){
        printf("Not enough memory!\n");
        return -1;
    }
    
    printf("Append A\n");
    appendNode(n1, 0, "A", 1, 12, 12);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Delete n1\n");
    emptyList(n1);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Append AA\n");
    appendNode(n1, 0, "AA", 2, 12, 12);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Append B\n");
    appendNode(n1, 5, "B", 1, 12, 12);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    emptyList(n1);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Append AAA\n");
    appendNode(n1, 0, "AAA", 3, 12, 12);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Append BB\n");
    appendNode(n1, 5, "BB", 2, 12, 12);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Append C\n");
    appendNode(n1, 6, "C", 1, 12, 12);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    emptyList(n1);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Append KOPHS\n");
    appendNode(n1, 0, "KOPHS", 5, 12, 12);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Append TESTS\n");
    appendNode(n1, 10, "TESTS", 5, 12, 12);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Append THESE\n");
    appendNode(n1, 234, "THESE", 15, 12, 12);
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
    
    printf("Append a1\n");
    appendNode(n1, 23, "a1", 2, 12, 12);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Append a2\n");
    appendNode(n1, 10, "a2", 2, 12, 12);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Append a3\n");
    appendNode(n1, 234, "a3", 2, 12, 12);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);

    printf("Append a4\n");
    appendNode(n1, 0, "a4", 2, 12, 12);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Append a5\n");
    appendNode(n1, 10, "a5", 2, 12, 12);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Append a6\n");
    appendNode(n1, 234, "a6", 2, 12, 12);
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
    
    printf("Append a7\n");
    appendNode(n1, 234, "a7", 2, 12, 12);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Append a7\n");
    appendNode(n1, 234, "a7", 2, 12, 12);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Append a1\n");
    appendNode(n1, 234, "a1", 2, 12, 12);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    printf("Append a3\n");
    appendNode(n1, 234, "a3", 2, 12, 12);
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
    
    printf("Append a8\n");
    appendNode(n1, 234, "a8", 2, 12, 12);
    bzero(buff, buffSize);
    BuffAllNodes(n1, buff, buffSize);
    printf("%s\n",buff);
    
    deleteList(n1);
    
    return 0;
}