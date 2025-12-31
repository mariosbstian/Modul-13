#include <iostream>
#include "multilist2.h"
using namespace std;

int main(){
    ListInduk L;
    initInduk(L);

    IndukPtr p1 = createIndukNode(1);
    IndukPtr p2 = createIndukNode(2);
    IndukPtr p3 = createIndukNode(3);

    insertFirstInduk(L, p1);
    insertLastInduk(L, p2);
    insertLastInduk(L, p3);

    insertLastAnak(p1->children, createAnakNode(10));
    insertLastAnak(p1->children, createAnakNode(20));
    insertLastAnak(p2->children, createAnakNode(30));
    insertLastAnak(p3->children, createAnakNode(40));
    insertLastAnak(p3->children, createAnakNode(50));

    cout << "=== DATA MULTI LINKED LIST ===" << endl;
    printMultiList(L);

    return 0;
}
