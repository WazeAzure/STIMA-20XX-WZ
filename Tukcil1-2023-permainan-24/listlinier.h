/* File : listlinier.h */
/* contoh ADT list berkait dengan representasi fisik pointer  */
/* Representasi address dengan pointer */
/* ElType adalah integer */

#ifndef listlinier_H
#define listlinier_H

#include "boolean.h"

/* Definisi Node : */
typedef int ElType;
typedef struct node* Address;
typedef struct node {
    ElType *info;
    Address next;
} Node;

#define INFO(p) (p)->info
#define NEXT(p) (p)->next

Address newNode(ElType val[4]);

/* Definisi List : */
/* List kosong : FIRST(l) = NULL */
/* Setiap elemen dengan Address p dapat diacu INFO(p), NEXT(p) */
/* Elemen terakhir list: jika addressnya Last, maka NEXT(Last)=NULL */

typedef Address List;

void CreateList(List *l);

void insertLast(List *l, ElType val[4]);

void printList(List l);

#endif