#ifndef CIRCULARLIST1_H
#define CIRCULARLIST1_H

#include <iostream>
using namespace std;

/* ===== TYPE ===== */
typedef struct Mahasiswa {
    string nama;
    string nim;
    char jenis_kelamin;
    float ipk;
} infotype;

typedef struct ElmNode *address;

struct ElmNode {
    infotype info;
    address next;
};

struct List {
    address first;
};

/* ===== FUNCTION & PROCEDURE ===== */
void initList(List &L);
address makeNode(string nama, string nim, char jenis_kelamin, float ipk);
void deleteNode(address &P);

void insertAtFront(List &L, address P);
void insertAtEnd(List &L, address P);
void insertAfterNode(List &L, address Prec, address P);

void deleteFront(List &L, address &P);
void deleteAfter(List &L, address Prec, address &P);
void deleteEnd(List &L, address &P);

address findNode(List L, infotype x);
void showList(List L);

#endif
