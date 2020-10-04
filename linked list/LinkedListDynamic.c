// In this dynamic implementation of a Linked List, we allocate memory as needed.

#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>

typedef int TYPEKEY;

typedef struct {
    TYPEKEY key;
} REG;

typedef struct aux {
    REG reg;
    struct aux* next;
} ITEM;

typedef ITEM* POINT;

typedef struct {
    POINT first;
} LIST;

void startList(LIST* l){
    l->first = NULL;
}

int listSize(LIST* l) {
    POINT end = l->first;
    int size = 0;
    while (end != NULL) {
        size++;
        end = end->next;
    }
    return size;
}

void printList(LIST* l){
    POINT end = l->first;
    printf("List: \" ");
    while (end != NULL) {
        printf("%i ", end->reg.key);
        end = end->next;
    }
    printf("\"\n");
}

POINT linearSearch(LIST* l, TYPEKEY ch) {
    POINT pos = l->first;
    while (pos != NULL) {
        if (pos->reg.key == ch) return pos;
        pos = pos->next;
    }
    return NULL;
}

POINT linearSearchOrdered(LIST* l, TYPEKEY ch) {
    POINT pos = l->first;
    while (pos != NULL && pos->reg.key < ch) pos = pos->next;
    if (pos != NULL && pos->reg.key == ch) return pos;
    return NULL;
}

POINT linearSearchExc(LIST* l, TYPEKEY ch, POINT* before){
    *before = NULL;
    POINT current = l->first;
    while ((current != NULL) && (current->reg.key < ch)) {
        *before = current;
        current = current->next;
    }
    if ((current != NULL) && (current->reg.key == ch)) return current;
    return NULL;
}

bool insertItemOrdered(LIST* l, REG reg) {
    TYPEKEY ch = reg.key;
    POINT before, i;
    i = linearSearchExc(l, ch, &before);
    if (i != NULL) return false;
    i = (POINT) malloc(sizeof(ITEM));
    i->reg = reg;
    if (before == NULL) {
        i->next = l->first;
        l->first = i;
    } else {
        i->next = before->next;
        before->next = i;
    }
    return true;
}

bool deleteItem(LIST* l, TYPEKEY ch) {
    POINT before, i;
    i = buscaSequencialExc(l, ch, &before);
    if (i == NULL) return false;
    if (before == NULL) l->first = i->next;
    else before->next = i->next;
    free(i);
    return true;
}

void restartList(LIST* l) {
    POINT end = l->first;
    while (end != NULL) {
        POINT delete = end;
        end = end->next;
        free(delete);
    }
    l->first = NULL;
}