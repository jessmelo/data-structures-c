// this linked list is circular, which means the last element points to the first

// we have an additional element called the head at the beggining 

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

typedef int TYPEKEY;

typedef struct {
    TYPEKEY key;
} REG;

typedef struct tempReg {
    REG reg;
    struct tempReg* next;
} ELEMENT;

typedef ELEMENT* POINTER;

typedef struct {
    POINTER head;
} LIST;

void initializeList(LIST* l) {
    l->head = (POINTER) malloc(sizeof(ELEMENT));
    l->head->next = l->head;
}

int listSize(LIST* l) {
    POINTER end = l->head->next;
    int size = 0;
    while (end != l->head) {
        size++;
        end = end->next;
    }
    return size;
}

void printList(LIST* l) {
    POINTER end = l->head->next;
    printf("LIST: \" ");
    while (end != l->head) {
    printf("%i ", end->reg.key);
    end = end->next;
    }
    printf("\"\n");
}

// search for non ordered lists
POINTER searchWithSentinel(LIST* l, TYPEKEY ch) {
    POINTER pos = l->head->next;
    l->head->reg.key = ch;
    while (pos->reg.key != ch) pos = pos->next;
    if (pos != l->head) return pos;
    return NULL;
}

// search for ordered lists
POINTER searchWithSentinalOrdered(LIST* l, TYPEKEY ch) {
    POINTER pos = l->head->next;
    l->head->reg.key = ch;
    while (pos->reg.key < ch) pos = pos->next;
    if (pos != l->head && pos->reg.key==ch) return pos;
    return NULL;
}

POINTER linearSearch(LIST* l, TYPEKEY ch, POINTER* ant) {
    *ant = l->head;
    POINTER current = l->head->next;
    l->head->reg.key = ch;
    while (current->reg.key<ch) {
        *ant = current;
        current = current->next;
    }
    if (current != l->head && current->reg.key == ch) return current;
    return NULL;
}

bool insertItemOrdered(LIST* l, REG reg) {
    POINTER ant, i;
    i = linearSearch(l,reg.key,&ant);
    if (i != NULL) return false;
    i = (POINTER) malloc(sizeof(ELEMENT));
    i->reg = reg;
    i->next = ant->next;
    ant->next = i;
    return true;
}

bool deleteItem(LIST* l, TYPEKEY ch) {
    POINTER ant, i;
    i = linearSearch(l,ch,&ant);
    if (i == NULL) return false;
    ant->next = i->next;
    free(i);
    return true;
}

void restartList(LIST* l) {
    POINTER end = l->head->next;
    while (end != l->head) {
        POINTER apagar = end;
        end = end->next;
        free(apagar);
    }
    l->head->next = l->head;
}

