#include <stdio.h>
#include <stdlib.h>
#include "listlinier.h"

Address newNode(ElType val) {
    Address p = (Address)malloc(sizeof(Node));
    if (p != NULL) {
        INFO(p) = val;
        NEXT(p) = NULL;
    }
    return p;
}
/* PROTOTYPE */
/****************** PEMBUATAN LIST KOSONG ******************/
void CreateList(List *l)
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
{
    FIRST(*l) = NULL;
}
/****************** TEST LIST KOSONG ******************/
boolean isEmpty(List l)
/* Mengirim true jika list kosong */
{
    return FIRST(l) == NULL;
}

/****************** GETTER SETTER ******************/
ElType getElmt(List l, int idx)
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengembalikan nilai elemen l pada indeks idx */
{
    int counter = 0;
    Address p = l;
    while (counter < idx) {
        p = NEXT(p);
        counter++;
    }
    return INFO(p);
}

void setElmt(List *l, int idx, ElType val)
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengubah elemen l pada indeks ke-idx menjadi val */
{
    int counter = 0;
    Address p = *l;
    while (counter < idx) {
        p = NEXT(p);
        counter++;
    }
    INFO(p) = val;
}

int indexOf(List l, ElType val)
/* I.S. l, val terdefinisi */
/* F.S. Mencari apakah ada elemen list l yang bernilai val */
/* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
/* Mengembalikan IDX_UNDEF jika tidak ditemukan */
{
    Address p = l;
    int counter = 0;
    while (p != NULL) {
        if(INFO(p) == val) {
            return counter;
        }
        counter++;
        p = NEXT(p);
    }
    return IDX_UNDEF;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertFirst(List *l, ElType val)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val jika alokasi berhasil. */
/* Jika alokasi gagal: I.S.= F.S. */
{
    Address p = newNode(val);
    if (p != NULL) {
        NEXT(p) = *l;
        *l = p;
    }
}

void insertLast(List *l, ElType val)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    if (isEmpty(*l)) {
        insertFirst(l, val);
    } else {
        Address p = newNode(val);;
        if (p!=NULL) {
            Address Last = *l;
            while(NEXT(Last) != NULL) {
                Last = NEXT(Last);
            }
            NEXT(Last) = p;
        }
    }
}

void insertAt(List *l, ElType val, int idx)
/* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menyisipkan elemen dalam list pada indeks ke-idx (bukan menimpa elemen di i) */
/* yang bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    if (idx == 0) {
        insertFirst(l, val);
    } else {
        Address p = newNode (val);
        if (p != NULL) {
            int counter = 0;
            Address loc = *l;
            while (counter < idx-1) {
                loc = NEXT(loc);
                counter++;
            }
            NEXT(p) = NEXT(loc);
            NEXT(loc) = p; 
        }
    }
}

/*** PENGHAPUSAN ELEMEN ***/
void deleteFirst(List *l, ElType *val)
/* I.S. List l tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada x */
/*      dan alamat elemen pertama di-dealokasi */
{
    Address p = *l;
    *val = INFO(*l);
    *l = NEXT(p);
    free(p);
}

void deleteLast(List *l, ElType *val)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada x */
/*      dan alamat elemen terakhir di-dealokasi */
{
    Address p, loc;
    p = *l;
    loc = NULL;
    while (NEXT(p) != NULL) {
        loc = p;
        p = NEXT(p);
    }
    if (loc == NULL) {
        *l = NULL;
    } else {
        NEXT(loc) = NULL;
    }
    *val = INFO(p);
    free(p);
}

void deleteAt(List *l, int idx, ElType *val)
/* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. val diset dengan elemen l pada indeks ke-idx. */
/*      Elemen l pada indeks ke-idx dihapus dari l */
{
    if (idx == 0) {
        deleteFirst(l, val);
    } else {
        int counter = 0;
        Address loc = *l;
        while (counter < idx - 1) {
            loc = NEXT(loc);
            counter++;
        }
        Address p = NEXT(loc);
        *val = INFO(p);
        NEXT(loc) = NEXT(p);
        free(p);
    }
}


/****************** PROSES SEMUA ELEMEN LIST ******************/
void displayList(List l)
// void printInfo(List l);
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
    printf("[");
    Address p = FIRST(l);
    while (p != NULL) {
        printf("%d", INFO(p));
        p = NEXT(p);
        if (p != NULL) {
            printf(",");
        }
    }
    printf("]");
}

int length(List l)
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
{
    Address p = l;
    int counter = 0;
    while (p != NULL) {
        counter++;
        p = NEXT(p);
    }
    return counter;
}

/****************** PROSES TERHADAP LIST ******************/
List concat(List l1, List l2)
/* I.S. l1 dan l2 sembarang */
/* F.S. l1 dan l2 kosong, l3 adalah hasil konkatenasi l1 & l2 */
/* Konkatenasi dua buah list : l1 dan l2    */
/* menghasilkan l3 yang baru (dengan elemen list l1 dan l2 secara beurutan). */
/* Tidak ada alokasi/dealokasi pada prosedur ini */
{
    List l3;
    CreateList(&l3);
    Address p = l1;
    while (p != NULL) {
        insertLast(&l3, INFO(p));
        p = NEXT(p);
    }
    p = l2;
    while (p!= NULL) {
        insertLast(&l3, INFO(p));
        p = NEXT(p);
    }
    return l3;
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
boolean fSearch(List L, Address P)
/* Mencari apakah ada elemen list yang beralamat P */
/* Mengirimkan true jika ada, false jika tidak ada */
{
    Address p = L;
    while ( p != NULL){
        if (p == P) {
            return true;
        }
        p = NEXT(p);
    }
    return false;
}
Address searchPrec(List L, ElType X)
/* Mengirimkan address elemen sebelum elemen yang nilainya=X */
/* Mencari apakah ada elemen list dengan Info(P)=X */
/* Jika ada, mengirimkan address Prec, dengan Next(Prec)=P dan Info(P)=X. */
/* Jika tidak ada, mengirimkan Nil */
/* Jika P adalah elemen pertama, maka Prec=Nil */
/* Search dengan spesifikasi seperti ini menghindari */
/* traversal ulang jika setelah Search akan dilakukan operasi lain */
{
    Address p = L;
    Address loc = NULL;
    boolean found = false;
    while (NEXT(p) != NULL) {
        loc = p;
        p = NEXT(p);
        if(INFO(p) == X) {
            return loc;
        }
    }
    return NULL;
}

/*** Prekondisi untuk Max/Min/Rata-rata : List tidak kosong ***/
ElType maxValue(List l)
{
    Address p = l;
    int x = INFO(p);
    while (p != NULL) {
        if (INFO(p) > x) {
            x = INFO(p);
        }
        p = NEXT(p);
    }
    return x;
}
/* Mengirimkan nilai info(P) yang maksimum */
Address adrMax(List l){
    Address p = l;
    int x = maxValue(l);
    while (p != NULL) {
        if (INFO(p) == x) {
            return p;
        }
        p = NEXT(p);
    }
}
/* Mengirimkan address P, dengan info(P) yang bernilai maksimum */
ElType minValue(List l)
{
    Address p = l;
    int x = INFO(p);
    while (p != NULL) {
        if (INFO(p) < x) {
            x = INFO(p);
        }
        p = NEXT(p);
    }
    return x;
}
/* Mengirimkan nilai info(P) yang minimum */
Address adrMin(List l)
{
    Address p = l;
    int x = minValue(l);
    while (p != NULL) {
        if (INFO(p) == x) {
            return p;
        }
        p = NEXT(p);
    }
}
/* Mengirimkan address P, dengan info(P) yang bernilai minimum */
float average(List L)
{
    float sum = 0, count = 0;
    Address p = L;
    while (p != NULL) {
        sum += (float)INFO(p);
        count++;
        p = NEXT(p);
    }
    if (count == 0) {
        return 0;
    } else {
        return sum/(count);
    }
}
/* Mengirimkan nilai rata-rata info(P) */

/***************** FUNGSI dan PROSEDUR TAMBAHAN **************/
void deleteAll(List *l)
/* Delete semua elemen list dan alamat elemen di-dealokasi */
{
    ElType buang;
    while ( *l != NULL )
    {
        deleteFirst(l,&buang);
    }
}

void copyList(List *l1, List *l2)
/* I.S. L1 sembarang. F.S. L2=L1 */
/* L1 dan L2 "menunjuk" kepada list yang sama.*/
/* Tidak ada alokasi/dealokasi elemen */
{
    *l2 = *l1;
}

void inverseList(List *l)
/* I.S. sembarang. */
/* F.S. elemen list dibalik : */
/* Elemen terakhir menjadi elemen pertama, dan seterusnya. */
/* Membalik elemen list, tanpa melakukan alokasi/dealokasi. */
{
    Address loc = NULL;
    Address p = *l;
    Address new_first;
    int jumlah = length(*l);
    while( NEXT(p) != NULL) {
        loc = p;
        p = NEXT(p);
    }
    new_first = p;
    NEXT(loc) = NULL;
    while ((NEXT(*l) != NULL)) {
        p = *l;
        while (NEXT(p) != NULL) {
            loc = p;
            p = NEXT(p);
        }
        Address j;
        j = new_first;
        while (NEXT(j) != NULL) {
            j = NEXT(j);
        }
        NEXT(j) = p;
        NEXT(loc) = NULL;
    }
    Address j;
    j = new_first;
    while(NEXT(j) != NULL) {
        j = NEXT(j);
    }
    NEXT(j) = *l;
    *l = new_first;
}


// int main() {
//     List l;
//     CreateList(&l);;
//     int i;
//     for(i = 0 ; i < 10 ; i++){
//         insertLast(&l, i);
//     }
//     displayList(l);
//     printf("\n");
//     inverseList(&l);
//     displayList(l);
//     return 0;
// }