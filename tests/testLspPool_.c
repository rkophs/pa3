
#include "../dependencies/shared_.h"

int main(int argc, char** argv) {
    int buffSize = 2048;
    char buff[buffSize];
    bzero(buff, buffSize);
    
    struct lspPool *n1;
    struct LSP *n2; struct LSP *n3; struct LSP *n4; struct LSP *n5;
    struct LSP *n6; struct LSP *n7; struct LSP *n8; struct LSP *n9;
    struct LSP *na; struct LSP *nb; struct LSP *nc;
    
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
    
    printf("Creating new pool\n");
    n1 = NULL; n2 = NULL; n3 = NULL; n4 = NULL; n5 = NULL; n6 = NULL; 
    n7 = NULL; n8 = NULL; n9 = NULL; na = NULL; nb = NULL; nc = NULL;
    
    n1 = createLSPPool();
    n2 = createLSP("B", 1, 11, 1);
    n3 = createLSP("B", 1, 12, 2);
    n4 = createLSP("C", 1, 13, 3);
    n5 = createLSP("C", 1, 14, 2);
    n6 = createLSP("C", 1, 14, 3);
    n7 = createLSP("C", 1, 14, 4);
    n8 = createLSP("B", 1, 15, 0);
    n9 = createLSP("D", 1, 16, 8);
    na = createLSP("D", 1, 17, 8);
    nb = createLSP("D", 1, 18, 9);
    nc = createLSP("D", 1, 19, 7);
    
    printf("Append n2:\n");
    shallowAppendLSP(n1, n2);
    bzero(buff, buffSize);
    BuffAllLSPs(n1, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Append n3 (shouldn't happen):\n");
    if(shallowAppendLSP(n1, n3) < 0){
        releaseLSP(n3);
    }
    bzero(buff, buffSize);
    BuffAllLSPs(n1, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Append n4:\n");
    shallowAppendLSP(n1, n4);
    bzero(buff, buffSize);
    BuffAllLSPs(n1, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Swapping in n6 (3 -> 3) shouldn't work\n");
    CmpSwapSingleLSP(n1, n6);
    bzero(buff, buffSize);
    BuffAllLSPs(n1, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Swapping in n7 (3 -> 4) shouldn't work\n");
    CmpSwapSingleLSP(n1, n7);
    bzero(buff, buffSize);
    BuffAllLSPs(n1, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Swapping in n5 (3 -> 2)\n");
    CmpSwapSingleLSP(n1, n5);
    bzero(buff, buffSize);
    BuffAllLSPs(n1, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Swapping in n7 (2 -> 4) shouldn't work\n");
    CmpSwapSingleLSP(n1, n7);
    bzero(buff, buffSize);
    BuffAllLSPs(n1, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Swapping in n8 (1 -> 0)\n");
    CmpSwapSingleLSP(n1, n8);
    bzero(buff, buffSize);
    BuffAllLSPs(n1, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Append n9:\n");
    shallowAppendLSP(n1, n9);
    bzero(buff, buffSize);
    BuffAllLSPs(n1, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Swapping in na (8 -> 8) Shouldn't work\n");
    CmpSwapSingleLSP(n1, na);
    bzero(buff, buffSize);
    BuffAllLSPs(n1, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Swapping in nb (8 -> 9) Shouldn't work\n");
    CmpSwapSingleLSP(n1, nb);
    bzero(buff, buffSize);
    BuffAllLSPs(n1, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Swapping in nc (8 -> 7)\n");
    CmpSwapSingleLSP(n1, nc);
    bzero(buff, buffSize);
    BuffAllLSPs(n1, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Get 0 it:\n");
    struct LSP *tmp = getLSPByIt(n1, 0);
    bzero(buff, buffSize);
    BuffLSP(tmp, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Get 1 it:\n");
    tmp = getLSPByIt(n1, 1);
    bzero(buff, buffSize);
    BuffLSP(tmp, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Get 2 it:\n");
    tmp = getLSPByIt(n1, 2);
    bzero(buff, buffSize);
    BuffLSP(tmp, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Get 3 it:\n");
    tmp = getLSPByIt(n1, 3);
    bzero(buff, buffSize);
    BuffLSP(tmp, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Get A:\n");
    tmp = getLSPByName(n1, "A");
    bzero(buff, buffSize);
    BuffLSP(tmp, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Get B:\n");
    tmp = getLSPByName(n1, "B");
    bzero(buff, buffSize);
    BuffLSP(tmp, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Get C:\n");
    tmp = getLSPByName(n1, "C");
    bzero(buff, buffSize);
    BuffLSP(tmp, buff, buffSize);
    printf("%s\n", buff);
    
    printf("Get D:\n");
    tmp = getLSPByName(n1, "D");
    bzero(buff, buffSize);
    BuffLSP(tmp, buff, buffSize);
    printf("%s\n", buff);
    
    releaseLSPPool(n1);
    releaseLSP(n2);
    releaseLSP(n3);
    releaseLSP(n4);
    releaseLSP(n5);
    releaseLSP(n6);
    releaseLSP(n7);
    releaseLSP(n8);
    releaseLSP(n9);
    releaseLSP(na);
    releaseLSP(nb);
    releaseLSP(nc);
    
    return (EXIT_SUCCESS);
}

