// In a static list, we use an array to allocate memory for our list.

#include <stdbool.h>
#include <stdio.h>

#define MAX 50
#define INVALID -1

typedef int TYPEKEY;

typedef struct{
    TYPEKEY key;
} REG;

typedef struct{
    REG reg;
    int next; // each item has a pointer to the next item on the list
} ITEM;

typedef struct {
    ITEM A[MAX];
    int first; // pointer to the first item on the list
    int free; // pointer to the fist free element on the list
} LIST;

void startList(LIST* l){
    int i;
    for (i=0; i < MAX-1; i++){
        l->A[i].next = i + 1;
    }
    l->A[MAX-1].next = INVALID;
    l->first = INVALID;
    l->free = 0;
}

int listSize(LIST* l){
    int i = l->first;
    int size = 0;
    while (i != INVALID) {
        size++;
        i = l->A[i].next;
    }
    return size;
}

void printList(LIST* l) {
    int i = l->first;
    printf("List: \" ");
    while (i != INVALID) {
        printf("%i ", l->A[i].reg.key);
        i = l->A[i].next;
    }
    printf("\"\n");
}

int linearSearch(LIST* l, TYPEKEY key) {
    int i = l->first;
    while (i != INVALID && l->A[i].reg.key < key){
        i = l->A[i].next;
    }
    if (i != INVALID && l->A[i].reg.key == key){
        return i;
    }
    else return INVALID;
}

int getFreePosition(LIST* l) {
    int result = l->free;
    if (l->free != INVALID){
        l->free = l->A[l->free].next;
    }
    return result;
}

void freeItemPosition(LIST* l, int j) {
    l->A[j].next = l->free;
    l->free = j;
}

bool insertItem(LIST* l, REG reg) {
    if (l->free == INVALID) return false;
    int before = INVALID;
    int i = l->first;
    TYPEKEY key = reg.key;
    while ((i != INVALID) && (l->A[i].reg.key < key)){
        before = i;
        i = l->A[i].next;
    }
    if (i!=INVALID && l->A[i].reg.key == key) return false;
    i = getFreePosition(l);
    l->A[i].reg = reg;
    if (before == INVALID) {
        l->A[i].next = l->first;
        l->first = i;
    } else {
        l->A[i].next = l->A[before].next;
        l->A[before].next = i;
    }
    return true;
}

bool deleteItem(LIST* l, TYPEKEY key) {
    int before = INVALID;
    int i = l->first;
    while ((i != INVALID) && (l->A[i].reg.key < key)) {
        before = i;
        i = l->A[i].next;
    }
    if (i == INVALID || l->A[i].reg.key != key) return false;
    if (before == INVALID) l->first = l->A[i].next;
    else l->A[before].next = l->A[i].next;
    freeItemPosition(l, i);
    return true;
}

void restartList(LIST* l) {
    startList(l);
}