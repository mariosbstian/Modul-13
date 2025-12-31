#include "circularlist1.h"
#include <iostream>
using namespace std;

int main() {
    List L;
    address P1, P2;
    infotype temp;

    initList(L);

    cout << "coba insert first, last, dan after" << endl;

    P1 = makeNode("Danu", "04", 'l', 4.0);
    insertAtFront(L, P1);

    P1 = makeNode("Fahmi", "06", 'l', 3.45);
    insertAtEnd(L, P1);

    P1 = makeNode("Bobi", "02", 'l', 3.71);
    insertAtFront(L, P1);

    P1 = makeNode("Ali", "01", 'l', 3.3);
    insertAtFront(L, P1);

    P1 = makeNode("Gita", "07", 'p', 3.75);
    insertAtEnd(L, P1);

    temp.nim = "07";
    P1 = findNode(L, temp);
    P2 = makeNode("Cindi", "03", 'p', 3.5);
    insertAfterNode(L, P1, P2);

    temp.nim = "02";
    P1 = findNode(L, temp);
    P2 = makeNode("Hilmi", "08", 'p', 3.3);
    insertAfterNode(L, P1, P2);

    temp.nim = "04";
    P1 = findNode(L, temp);
    P2 = makeNode("Eli", "05", 'p', 3.4);
    insertAfterNode(L, P1, P2);

    showList(L);

    return 0;
}
