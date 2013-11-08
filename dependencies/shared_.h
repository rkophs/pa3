#include <stdlib.h>

void insertNum(char * buffer, int buffSize, int num, int leastSignificantPos){
    if(num == 0){
        buffer[leastSignificantPos] = '0';
        return;
    }
    if(num < 0 || num > buffSize){
        buffer[leastSignificantPos] = '1';
        buffer[leastSignificantPos - 1] = '-';
        return;
    }
    int tmp = num;
    int i = leastSignificantPos;
    while(tmp){
        buffer[i] = tmp % 10 + 48;
        tmp /= 10;
        i--;
    }
}