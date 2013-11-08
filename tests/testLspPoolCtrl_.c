
#include "../dependencies/shared_.h"

int main(int argc, char** argv) {

    struct lspPool *pool;
    int buffSize = 1024;
    char buff[buffSize];
    bzero(buff, buffSize);
    
    struct LSP *n1; struct LSP *n2; struct LSP *n3; struct LSP *n4; struct LSP *n5;
    struct LSP *n6; struct LSP *n7; struct LSP *n8; struct LSP *n9; struct LSP *na;
    
    pool = createLSPPool();
    n1 = createLSP("A", 1, 10, 5);
    BuffLSP(n1, buff, buffSize);
    printf("%s\n", buff);
    n2 = createLSP("B", 1, 11, 5);
    n3 = createLSP("C", 1, 12, 5);
    n4 = createLSP("B", 1, 13, 5);
    n5 = createLSP("B", 1, 14, 6);
    n6 = createLSP("B", 1, 15, 4);
    n7 = createLSP("D", 1, 16, 5);
    n8 = createLSP("E", 1, 17, 5);
    n9 = createLSP("A", 1, 18, 3);
    na = createLSP("A", 1, 19, 4);
    
    printf("passing n1, (A, 5)\n");
    lspPoolCtrl(pool, n1);
    bzero(buff, buffSize);
    BuffAllLSPs(pool, buff, buffSize);
    printf("%s\n", buff);
    
    printf("passing n2, (B, 5)\n");
    lspPoolCtrl(pool, n2);
    bzero(buff, buffSize);
    BuffAllLSPs(pool, buff, buffSize);
    printf("%s\n", buff);
    
    printf("passing n3, (C, 5)\n");
    lspPoolCtrl(pool, n3);
    bzero(buff, buffSize);
    BuffAllLSPs(pool, buff, buffSize);
    printf("%s\n", buff);
    
    printf("passing n4, (B, 5)\n");
    lspPoolCtrl(pool, n4);
    bzero(buff, buffSize);
    BuffAllLSPs(pool, buff, buffSize);
    printf("%s\n", buff);
    
    printf("passing n5, (B, 6)\n");
    lspPoolCtrl(pool, n5);
    bzero(buff, buffSize);
    BuffAllLSPs(pool, buff, buffSize);
    printf("%s\n", buff);
    
    printf("passing n6, (B, 4)\n");
    lspPoolCtrl(pool, n6);
    bzero(buff, buffSize);
    BuffAllLSPs(pool, buff, buffSize);
    printf("%s\n", buff);
    
    printf("passing n7, (D, 5)\n");
    lspPoolCtrl(pool, n7);
    bzero(buff, buffSize);
    BuffAllLSPs(pool, buff, buffSize);
    printf("%s\n", buff);
    
    printf("passing n8, (E, 5)\n");
    lspPoolCtrl(pool, n8);
    bzero(buff, buffSize);
    BuffAllLSPs(pool, buff, buffSize);
    printf("%s\n", buff);
    
    printf("passing n9, (A, 3)\n");
    lspPoolCtrl(pool, n9);
    bzero(buff, buffSize);
    BuffAllLSPs(pool, buff, buffSize);
    printf("%s\n", buff);
    
    printf("passing na, (A, 4)\n");
    lspPoolCtrl(pool, na);
    bzero(buff, buffSize);
    BuffAllLSPs(pool, buff, buffSize);
    printf("%s\n", buff);
    
    releaseLSPPool(pool);
    
    return (EXIT_SUCCESS);
}

