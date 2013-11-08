#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define COSTMAX 9999999
#define COSTMEM 8

struct Node {
    char name[32];
    int cost;
    struct Node *next;
};

struct Node *initList(){
    struct Node *tmp;
    if ((tmp = (struct Node *) malloc(sizeof (struct Node))) == NULL) {
        return NULL; //Not enough memory
    }
    tmp->cost = -2;
    bzero(tmp->name, sizeof(tmp->name));
    tmp->next = NULL;
}

int appendNode(struct Node *list, int cost, char *name, int nameLength) {
    struct Node *tmp;
    if ((tmp = (struct Node *) malloc(sizeof (struct Node))) == NULL) {
        return -1; //Not enough memory
    }
    if (nameLength < sizeof (tmp->name)) { //prevent buffer overflows
        bzero(tmp->name, sizeof(tmp->name));
        strncpy(tmp->name, name, nameLength);
    } else {
        free(tmp);
        return -1;
    }
    tmp->cost = cost;
    tmp->next = NULL;
    
    struct Node *it;
    struct Node *linker;
    it = list->next;
    linker = list;
    while (it != NULL) { //Iterate to end position
        if(!strcmp(it->name, name)){
            return -1; //already exists;
        }
        linker = it;
        it = it->next;
    }
    linker->next = tmp;
    return 0;
}

int deleteNode(struct Node *list, char *name) {
    if (list == NULL || list->cost != -2) { //Not a valid header
        return -1;
    }

    struct Node *curr = list->next;
    struct Node *prev = list;
    while (curr != NULL) {
        if (!strcmp(curr->name, name)) {
            //match, now delete:
            struct Node *tmp = curr->next;
            free(curr);
            curr = NULL;
            prev->next = tmp;
            return 0;
        } else {
            curr = curr->next;
            prev = prev->next;
        }
    }
    return -1;
}

void emptyList(struct Node *target){
    if(target == NULL || target->cost != -2){ //Not a header
        return;
    }
    struct Node *it1;
    struct Node *tmp;
    
    it1 = target->next;
    while (it1->next != NULL) {
        tmp = it1->next;
        free(it1);
        it1 = tmp;
    }
    target->next = NULL;
}

void deleteList(struct Node *target) {
    if(target == NULL){ //Already no memory
        return;
    }
    emptyList(target);
    free(target);
    target = NULL;
}

//Insert a number into a header buffer in appropriate way:
void insertNum(char * buffer, int num, int leastSignificantPos){
    if(num == 0){
        buffer[leastSignificantPos] = '0';
        return;
    }
    if(num < 0 || num > COSTMAX){
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

int printAllNodes(struct Node *target, char *buff, int size){
    if(target == NULL || target->cost != -2){ //Must be valid list header
        return -1;
    }
    
    bzero(buff, size);
    struct Node *it;
    it = target->next;
    
    int i = 0;
    while(it != NULL){
        if((i + strlen(it->name) + (COSTMEM - 1) + 3) >= size){
            return -1; //Not enough buffer to continue
        }
        strcat(buff, "<");
        strncat(buff, it->name, strlen(it->name));
        strcat(buff, ",");
        
        char costStr[COSTMEM];
        memset(costStr,' ', COSTMEM);
        insertNum(costStr, it->cost, COSTMEM - 2);
        strncat(buff, costStr, COSTMEM - 1);
        strcat(buff, ">");
        it = it->next;
    }
    
    buff[size - 1] = 0; //security
    return 0;
}