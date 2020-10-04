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

void restartList(LIST* l){
    l->numItems = 0;
}

bool insertItem(LIST* l, ITEM i){
    if(l->numItems == MAX) return false;
    int index = l->numItems; 
    while(index > 0 && l->A[index-1].key > i.key) {
        l->A[index] = l->A[index-1];
        index--;
    }
    l->A[index] = i;
    l->numItems = l->numItems+1;
    return true;
}

int binarySearch(LIST* l, KEYTYPE key){
    int left, right, center;
    left = 0;
    right = l->numItems-1;
    while(left <= right){
        center = ((left + right) / 2);
        if(l->A[center].key == key) return center;
        else {
            if(l->A[center].key < key) left = center+1;
            else right = center -1;
        }
    }
    return -1;
}

bool deleteItem(LIST* l, KEYTYPE key){
    int pos = binarySearch(l, key);
    if(pos == -1) return false;
    int j;
    for(j = pos; j < l->numItems-1; j++){
        l->A[j] = l->A[j+1];
    }
    l->numItems = l->numItems-1;
    return true;
}