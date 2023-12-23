#include <stdio.h>
#include <stdlib.h>
#include "listlinierS.h"

AddressS newNode(ElTypeS val[30]) {
    AddressS p = (AddressS)malloc(sizeof(NodeS));

    char* arr = (char*)malloc(sizeof(char) * 30);
    arr = val;

    if (p != NULL) {
        INFO(p) = arr;
        NEXT(p) = NULL;
    }
    return p;
}

void CreateListS(ListS *l){
    *l = NULL;
}

void insertLastS(ListS *l, ElTypeS val[30]){
    AddressS new = newNode(val);

    // printf("isi NEW -- ");
    // printList(new);

    if(new != NULL){
        if(*l == NULL){
            *l = new;
            // printf("called\n");
        } else {
            AddressS first = *l;
            while(first != NULL){
                first = NEXT(first);
            }

            NEXT(first) = new;
        }
    }
}

void printListS(ListS l){
    AddressS p = l;
    while(p != NULL){
        printf("%s\n", p->info);
        p = NEXT(p);
    }
}