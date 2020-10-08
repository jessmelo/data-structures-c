#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

typedef struct {
    int key;
} ITEM;

typedef struct aux {
    ITEM reg;
    struct aux* prox;
} ELEMENT;

typedef ELEMENT* POINTER; // creating a new type POINTER for element addresses

typedef struct {
    POINTER top;
} STACK;

void initializeStack(STACK* p){
    p->top = NULL;
}

int stackSize(STACK* p){
    POINTER end = p->top;
    int size = 0;
    while (end != NULL){
        size++;
        end = end->prox;
    }
    return size;
}

bool isEmpty(STACK* p){
    if(p->top == NULL) return true;
    return false;
}

void printStack(STACK* p){
    POINTER end = p->top;
    printf("Stack: ");
    while(end != NULL){
        printf("&i ", end->reg.key);
        end = end->prox;
    }
    printf("\"\n");
}

bool pushElement(STACK* p, ITEM reg){
    POINTER new = (POINTER) malloc(sizeof(ELEMENT));
    new->reg = reg;
    new->prox = p->top;
    p->top = new;
    return true;
}

bool popElement(STACK* p, ITEM* reg){
    if(p->top == NULL) return false;
    *reg = p->top->reg;
    POINTER del = p->top;
    p->top = p->top->prox;
    free(del);
    return true;
}

void restartStack(STACK* p){
    POINTER del;
    POINTER pos = p->top;
    while (pos != NULL){
        del = pos;
        pos = pos->prox;
        free(del);
    }
    p->top = NULL;
}