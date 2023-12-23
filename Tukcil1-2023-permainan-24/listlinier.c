#include <stdio.h>
#include <stdlib.h>
#include "listlinier.h"

Address newNode(ElType val[4]) {
    Address p = (Address)malloc(sizeof(Node));

    int* arr = (int*)malloc(sizeof(int) * 4);
    for(int i=0; i<4; i++){
        arr[i] = val[i];
    }

    if (p != NULL) {
        INFO(p) = arr;
        NEXT(p) = NULL;
    }
    return p;
}

void CreateList(List *l){
    *l = NULL;
}

void insertLast(List *l, ElType val[4]){
    Address new = newNode(val);

    // printf("isi NEW -- ");
    // printList(new);

    if(new != NULL){
        if(*l == NULL){
            *l = new;
            // printf("called\n");
        } else {
            Address first = *l;
            while(first != NULL){
                // cek array
                // printf("nilai linkedlist == %d %d %d %d\n", first->info[0], first->info[1], first->info[2], first->info[3]);
                if(first->info[0] == val[0] && first->info[1] == val[1] && first->info[2] == val[2] && first->info[3] == val[3]){
                    // printf("YES\n");
                    return;
                }
                first = NEXT(first);
            }

            first = *l;
            while(NEXT(first) != NULL){
                first = NEXT(first);
            }
            NEXT(first) = new;
        }
    }
}

void printList(List l){
    Address p = l;
    while(p != NULL){
        for(int i=0; i<4; i++){
            printf("%d ", p->info[i]);
        }
        printf("\n");

        p = NEXT(p);
    }
}