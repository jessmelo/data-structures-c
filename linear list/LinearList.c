#include <stdbool.h>
#include <stdio.h>

#define MAX 50 // sets the maximum number of items to 50

typedef int KEYTYPE; // type KEYTYPE is an integer

typedef struct {
    KEYTYPE key;
} ITEM;

typedef struct {
    ITEM A[MAX+1]; // adding a last element for sentinel
    int numItems; // number of elements
} LIST;

void startList(LIST* l){
    l->numItems = 0;
}

int listSize(LIST* l){
    return l->numItems;
}

void printList(LIST* l){
    int i;
    printf("List: \n");
    for (i=0; i < l->numItems; i++){
        printf("%i ", l->A[i].key);
    }
}

int linearSearch(LIST* l, KEYTYPE key){
    int i;
    for(i=0; i < l->numItems; i++){
        if(l->A[i].key == key) return i; // returns the position of the element
    }
    return -1;
}

int linearSearchWithSentinel(LIST* l, KEYTYPE key){
    int i = 0;
    // we're gonna add the key that we're searching to end of the list
    l->A[l->numItems].key = key;
    while (l->A[i].key != key) i++;
    if(i == l->numItems) return -1;
    else return i;
}

bool insertItem(LIST* l, ITEM i, int index){
    if(l->numItems == MAX || index < 0 || index > MAX) return false;
    int j;
    for (j = l->numItems; j > index; j--){
        l->A[j] = l->A[j-1];
    }
    l->A[index] = i;
    l->numItems = l->numItems+1;
    return true;
}

bool deleteItem(LIST* l, KEYTYPE key){
    int index = linearSearch(l, key);
    if(index == -1) return false;
    int i;
    for(i = index; i < l->numItems-1; i++){
        l->A[i] = l->A[i+1];
    }
    l->numItems = l->numItems-1;
    return true;
}

void restartList(LIST* l){
    l->numItems = 0;
}