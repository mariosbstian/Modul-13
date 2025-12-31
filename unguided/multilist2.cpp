#include "multilist2.h"

/* ===== CEK KOSONG ===== */
Bool isEmptyInduk(ListInduk L){
    return (L.first == NIL);
}

Bool isEmptyAnak(ListAnak L){
    return (L.first == NIL);
}

/* ===== INIT ===== */
void initInduk(ListInduk &L){
    L.first = L.last = NIL;
}

void initAnak(ListAnak &L){
    L.first = L.last = NIL;
}

/* ===== ALOKASI ===== */
IndukPtr createIndukNode(IndukData x){
    IndukPtr P = new NodeInduk;
    P->val = x;
    initAnak(P->children);
    P->next = P->prev = NIL;
    return P;
}

AnakPtr createAnakNode(AnakData x){
    AnakPtr P = new NodeAnak;
    P->val = x;
    P->next = P->prev = NIL;
    return P;
}

/* ===== DEALOKASI ===== */
void freeIndukNode(IndukPtr P){
    delete P;
}

void freeAnakNode(AnakPtr P){
    delete P;
}

/* ===== INSERT INDUK ===== */
void insertFirstInduk(ListInduk &L, IndukPtr P){
    if(isEmptyInduk(L)){
        L.first = L.last = P;
    } else {
        P->next = L.first;
        L.first->prev = P;
        L.first = P;
    }
}

void insertLastInduk(ListInduk &L, IndukPtr P){
    if(isEmptyInduk(L)){
        insertFirstInduk(L,P);
    } else {
        L.last->next = P;
        P->prev = L.last;
        L.last = P;
    }
}

void insertAfterInduk(ListInduk &L, IndukPtr P, IndukPtr Prec){
    P->next = Prec->next;
    P->prev = Prec;
    if(Prec->next != NIL) Prec->next->prev = P;
    else L.last = P;
    Prec->next = P;
}

/* ===== INSERT ANAK ===== */
void insertLastAnak(ListAnak &L, AnakPtr P){
    if(isEmptyAnak(L)){
        L.first = L.last = P;
    } else {
        L.last->next = P;
        P->prev = L.last;
        L.last = P;
    }
}

/* ===== DELETE INDUK ===== */
void deleteFirstInduk(ListInduk &L, IndukPtr &P){
    P = L.first;
    L.first = P->next;
    if(L.first != NIL) L.first->prev = NIL;
    else L.last = NIL;
    P->next = NIL;
}

void deleteLastInduk(ListInduk &L, IndukPtr &P){
    P = L.last;
    L.last = P->prev;
    if(L.last != NIL) L.last->next = NIL;
    else L.first = NIL;
    P->prev = NIL;
}

/* ===== PRINT ===== */
void printMultiList(ListInduk L){
    IndukPtr P = L.first;
    while(P != NIL){
        cout << "Induk : " << P->val << " -> Anak : ";
        AnakPtr A = P->children.first;
        while(A != NIL){
            cout << A->val << " ";
            A = A->next;
        }
        cout << endl;
        P = P->next;
    }
}
