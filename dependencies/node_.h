
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXNODE 60

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
            free(tmp);
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
        }
        curr = curr->next;
        prev = prev->next;
    }
    return -1;
}

void emptyList(struct Node *target){
    if(target == NULL || target->cost != -2){ //Not a header
        return;
    }
    struct Node *it;
    struct Node *tmp;
    
    it = target->next;
    while (it != NULL) {
        tmp = it->next;
        free(it);
        it = tmp;
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