#ifndef MULTILIST2_H
#define MULTILIST2_H

#include <iostream>
using namespace std;

#define NIL NULL
typedef bool Bool;

typedef int AnakData;
typedef int IndukData;

struct NodeAnak;
struct NodeInduk;

typedef NodeAnak* AnakPtr;
typedef NodeInduk* IndukPtr;

/* ===== STRUCT ANAK ===== */
struct NodeAnak {
    AnakData val;
    AnakPtr next;
    AnakPtr prev;
};

struct ListAnak {
    AnakPtr first;
    AnakPtr last;
};

/* ===== STRUCT INDUK ===== */
struct NodeInduk {
    IndukData val;
    ListAnak children;
    IndukPtr next;
    IndukPtr prev;
};

struct ListInduk {
    IndukPtr first;
    IndukPtr last;
};

/* ===== PROTOTYPE ===== */
Bool isEmptyInduk(ListInduk L);
Bool isEmptyAnak(ListAnak L);

void initInduk(ListInduk &L);
void initAnak(ListAnak &L);

IndukPtr createIndukNode(IndukData x);
AnakPtr createAnakNode(AnakData x);

void freeIndukNode(IndukPtr P);
void freeAnakNode(AnakPtr P);

void insertFirstInduk(ListInduk &L, IndukPtr P);
void insertAfterInduk(ListInduk &L, IndukPtr P, IndukPtr Prec);
void insertLastInduk(ListInduk &L, IndukPtr P);

void insertLastAnak(ListAnak &L, AnakPtr P);

void deleteFirstInduk(ListInduk &L, IndukPtr &P);
void deleteLastInduk(ListInduk &L, IndukPtr &P);

void printMultiList(ListInduk L);

#endif
