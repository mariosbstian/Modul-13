#include "circularlist1.h"

/* ===== INIT LIST ===== */
void initList(List &L) {
    L.first = nullptr;
}

/* ===== MAKE NODE ===== */
address makeNode(string nama, string nim, char jenis_kelamin, float ipk) {
    address P = new ElmNode;
    P->info.nama = nama;
    P->info.nim = nim;
    P->info.jenis_kelamin = jenis_kelamin;
    P->info.ipk = ipk;
    P->next = nullptr;
    return P;
}

/* ===== DELETE NODE ===== */
void deleteNode(address &P) {
    delete P;
    P = nullptr;
}

/* ===== INSERT ===== */
void insertAtFront(List &L, address P) {
    if (L.first == nullptr) {
        L.first = P;
        P->next = P;
    } else {
        address last = L.first;
        while (last->next != L.first) last = last->next;
        P->next = L.first;
        last->next = P;
        L.first = P;
    }
}

void insertAtEnd(List &L, address P) {
    if (L.first == nullptr) {
        insertAtFront(L, P);
    } else {
        address last = L.first;
        while (last->next != L.first) last = last->next;
        last->next = P;
        P->next = L.first;
    }
}

void insertAfterNode(List &L, address Prec, address P) {
    P->next = Prec->next;
    Prec->next = P;
}

/* ===== FIND NODE ===== */
address findNode(List L, infotype x) {
    if (L.first == nullptr) return nullptr;
    address P = L.first;
    do {
        if (P->info.nim == x.nim) return P;
        P = P->next;
    } while (P != L.first);
    return nullptr;
}

/* ===== SHOW LIST ===== */
void showList(List L) {
    if (L.first == nullptr) return;
    address P = L.first;
    do {
        cout << "Nama : " << P->info.nama << endl;
        cout << "NIM  : " << P->info.nim << endl;
        cout << "L/P  : " << P->info.jenis_kelamin << endl;
        cout << "IPK  : " << P->info.ipk << endl;
        cout << endl;
        P = P->next;
    } while (P != L.first);
}
