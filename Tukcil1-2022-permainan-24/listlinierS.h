/* File : listlinier.h */
/* contoh ADT list berkait dengan representasi fisik pointer  */
/* Representasi address dengan pointer */
/* ElType adalah integer */

#ifndef listlinier_H
#define listlinier_H

#include "boolean.h"

/* Definisi Node : */
typedef char ElTypeS;
typedef struct nodeS* AddressS;
typedef struct nodeS {
    ElTypeS *info;
    AddressS next;
} NodeS;

#define INFO(p) (p)->info
#define NEXT(p) (p)->next

AddressS newNode(ElTypeS val[30]);

/* Definisi List : */
/* List kosong : FIRST(l) = NULL */
/* Setiap elemen dengan Address p dapat diacu INFO(p), NEXT(p) */
/* Elemen terakhir list: jika addressnya Last, maka NEXT(Last)=NULL */

typedef AddressS ListS;

void CreateListS(ListS *l);

void insertLastS(ListS *l, ElTypeS val[4]);

void printListS(ListS l);

#endif