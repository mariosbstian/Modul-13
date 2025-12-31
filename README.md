# <h1 align="center">Laporan Praktikum Modul (13)</h1>
<p align="center">Mario Sebastian Barus</p>

## Dasar Teori
Linked list adalah struktur data dinamis yang memudahkan penyimpanan dan pengelolaan data menggunakan pointer. Multi linked list (MLL) memungkinkan setiap node induk memiliki beberapa anak, cocok untuk data bersifat hierarkis seperti kategori dan menu restoran. Sedangkan circular doubly linked list (CDLL) menghubungkan node secara melingkar dengan akses dua arah, mempermudah penambahan, penghapusan, dan traversal data. Intinya, MLL fokus pada hubungan hierarki, sementara CDLL menekankan keterhubungan melingkar antar node.
## Guided 

### mll.h
```C++
#ifndef MLL_H
#define MLL_H

#include <iostream>
#include <string>

using namespace std;

struct DataMakanan {
    string idMakanan;
    string namaMakanan;
    float harga;
};

struct KategoriMakanan {
    string idKategori;
    string namaKategori;
};

typedef struct nodeParent *NodeParent;
typedef struct nodeChild *NodeChild;

struct nodeChild {
    DataMakanan isidata;
    NodeChild next;
    NodeChild prev;
};

struct listAnak {
    NodeChild first;
    NodeChild last;
};

struct nodeParent {
    KategoriMakanan isidata;
    NodeParent next;
    NodeParent prev;
    listAnak L_Anak;
};

struct listInduk {
    NodeParent first;
    NodeParent last;
};

//isEmpty & create list
bool isEmptyInduk(listInduk LInduk);
bool isEmptyAnak(listAnak LAnak);
void createListInduk(listInduk &LInduk);
void createListAnak(listAnak &LAnak);

//alokasi & dealokasi
NodeParent alokasiNodeParent(string idKategori, string namaKategori);
NodeChild alokasiNodeChild(string idMakanan, string namaMakanan, float harga);
void dealokasiNodeChild(NodeChild &nodeAnak);
void dealokasiNodeParent(NodeParent &nodeInduk);

//operasi pada parent
void insertFirstParent(listInduk &LInduk, NodeParent nodeBaruParent);
void insertLastParent(listInduk &LInduk, NodeParent nodeBaruParent);
void insertAfterParent(listInduk &LInduk, NodeParent nodeBaruParent, NodeParent nodePrevParent);
void deleteFirstParent(listInduk &LInduk);
void deleteLastParent(listInduk &LInduk);
void deleteAfterParent(listInduk &LInduk, NodeParent nodePrev);
void findParentByID(listInduk &LInduk, string IDCari);
void updateDataParentByID(listInduk &LInduk, string IDCari, string newNamaKategori);

//operasi pada child
void insertFirstChild(listAnak &LAnak, NodeChild nodeBaruChild);
void insertLastChild(listAnak &LAnak, NodeChild nodeBaruChild);
void insertAfterChild(listAnak &LAnak, NodeChild nodeBaruChild, NodeChild nodePrevChild);
void deleteFirstChild(listAnak &LAnak);
void deleteLastChild(listAnak &LAnak);
void deleteAfterChild(listAnak &LAnak, NodeChild nodePrev);
void findChildByID(listInduk &LInduk, string IDCari);
void updateDataChildByID(listInduk &LInduk, string IDCari, string newNamaMakanan, float newHarga);

//operasi print
void printStrukturMLL(listInduk &LInduk);
void printListInduk(listInduk &LInduk);
void printListAnak(listInduk &LInduk, NodeParent nodeInduk);

//operasi hapus list
void hapusListInduk(listInduk &LInduk);
void hapusListAnak(listAnak &LAnak);

#endif

```
### MLL.CPP
```c++
#include "mll.h"
#include <iostream>
#include <string>

using namespace std;

//isEmpty & create list
bool isEmptyInduk(listInduk LInduk){
    if(LInduk.first == NULL){
        return true;
    } else {
        return false;
    }
}

bool isEmptyAnak(listAnak LAnak){
    if(LAnak.first == NULL){
        return true;
    } else {
        return false;
    }
}

void createListInduk(listInduk &LInduk) {
    LInduk.first = LInduk.last = NULL;
}

void createListAnak(listAnak &LAnak) {
    LAnak.first = LAnak.last = NULL;
}

//alokasi & dealokasi
NodeParent alokasiNodeParent(string idKategori, string namaKategori) {
    NodeParent nodeBaruParent = new nodeParent;
    nodeBaruParent->isidata.idKategori = idKategori;
    nodeBaruParent->isidata.namaKategori = namaKategori;
    nodeBaruParent->next = NULL;
    nodeBaruParent->prev = NULL;
    createListAnak(nodeBaruParent->L_Anak);
    return nodeBaruParent;
}

NodeChild alokasiNodeChild(string idMakanan, string namaMakanan, float harga) {
    NodeChild nodeBaruChild = new nodeChild;
    nodeBaruChild->isidata.idMakanan = idMakanan;
    nodeBaruChild->isidata.namaMakanan = namaMakanan;
    nodeBaruChild->isidata.harga = harga;
    nodeBaruChild->next = NULL;
    nodeBaruChild->prev = NULL;
    return nodeBaruChild;
}

void dealokasiNodeChild(NodeChild &nodeAnak) {
    if(nodeAnak != NULL) {
        nodeAnak->next = nodeAnak->prev = NULL;
        delete nodeAnak;
        nodeAnak = NULL;
    }
}

void dealokasiNodeParent(NodeParent &nodeInduk) {
    if(nodeInduk != NULL) {
        nodeInduk->next = nodeInduk->prev = NULL;
        delete nodeInduk;
        nodeInduk = NULL;
    }
}

//operasi pada parent
void insertFirstParent(listInduk &LInduk, NodeParent nodeBaruParent) {
    if(isEmptyInduk(LInduk) == true) {
        LInduk.first = LInduk.last = nodeBaruParent;
    } else {
        nodeBaruParent->next = LInduk.first;
        LInduk.first->prev = nodeBaruParent;
        LInduk.first = nodeBaruParent;
    }
    cout << "Node parent "<< nodeBaruParent->isidata.namaKategori << " berhasil ditambahkan kedalam urutan pertama di list Induk!" << endl;
}

void insertLastParent(listInduk &LInduk, NodeParent nodeBaruParent) {
    if(isEmptyInduk(LInduk) == true) {
        LInduk.first = LInduk.last = nodeBaruParent;
    } else {
        nodeBaruParent->prev = LInduk.last;
        LInduk.last->next = nodeBaruParent;
        LInduk.last = nodeBaruParent;
    }
    cout << "Node parent "<< nodeBaruParent->isidata.namaKategori << " berhasil ditambahkan kedalam urutan terakhir di list Induk!" << endl;
}

void insertAfterParent(listInduk &LInduk, NodeParent nodeBaruParent, NodeParent nodePrevParent) {
    if(nodePrevParent == NULL) {
        cout << "Node Prev Parent tidak valid!" << endl;
    } else {
        if(nodePrevParent == LInduk.last){
            insertLastParent(LInduk, nodeBaruParent);
            return;
        } else {
            nodeBaruParent->next = nodePrevParent->next;
            nodeBaruParent->prev = nodePrevParent;
            (nodePrevParent->next)->prev = nodeBaruParent;
            nodePrevParent->next = nodeBaruParent;
            cout << "Node parent "<< nodeBaruParent->isidata.namaKategori << " berhasil ditambahkan kedalam list induk setelah node parent "<< nodePrevParent->isidata.namaKategori << endl;
        }
    }
}

void deleteFirstParent(listInduk &LInduk){
    if(isEmptyInduk(LInduk) == true){
        cout << "List Induk kosong!" << endl;
    } else {
        NodeParent nodeHapus = LInduk.first;
        if (LInduk.first == LInduk.last) { // KASUS KHUSUS 1 ELEMEN
            LInduk.first = NULL;
            LInduk.last = NULL;
        } else {
            LInduk.first = LInduk.first->next;
            LInduk.first->prev = NULL;
            nodeHapus->next = NULL;
        }
        if(nodeHapus->L_Anak.first != NULL){
            hapusListAnak(nodeHapus->L_Anak);
        }
        dealokasiNodeParent(nodeHapus);
        cout << "Node pertama list induk berhasil dihapus beserta anak-anaknya!" << endl;
    }
}

void deleteLastParent(listInduk &LInduk){
    if(isEmptyInduk(LInduk) == true){
        cout << "List Induk kosong!" << endl;
    } else {
        NodeParent nodeHapus = LInduk.last;
        if (LInduk.first == LInduk.last) {
            LInduk.first = NULL;
            LInduk.last = NULL;
        } else {
            LInduk.last = LInduk.last->prev;
            nodeHapus->prev = NULL;
            LInduk.last->next = NULL;
        }
        if(nodeHapus->L_Anak.first != NULL){
            hapusListAnak(nodeHapus->L_Anak);
        }
        dealokasiNodeParent(nodeHapus);
        cout << "Node terakhir list induk berhasil dihapus beserta anak-anaknya!" << endl;
    }
}

void deleteAfterParent(listInduk &LInduk, NodeParent nodePrev){
    if(isEmptyInduk(LInduk) == true){
        cout << "List induk kosong!" << endl;
    } else {
        if(nodePrev != NULL && nodePrev->next != NULL){
            NodeParent nodeHapus = nodePrev->next;
            nodePrev->next = nodeHapus->next;
            if (nodeHapus->next != NULL){
                (nodeHapus->next)->prev = nodePrev;
            } else {
                LInduk.last = nodePrev;
            }
            nodeHapus->next = NULL;
            if(nodeHapus->L_Anak.first != NULL){
                hapusListAnak(nodeHapus->L_Anak);
            }
            dealokasiNodeParent(nodeHapus);
            cout << "Node parent setelah node " << nodePrev->isidata.namaKategori << " berhasil dihapus beserta anak-anaknya!" << endl;
        } else {
            cout << "Node prev tidak valid!" << endl;
        }
    }
}

void findParentByID(listInduk &LInduk, string IDCari){
    if(isEmptyInduk(LInduk) == true){
        cout << "List induk kosong!" << endl;
    } else {
        NodeParent nodeBantu = LInduk.first;
        int index = 1;
        int ketemu = false;
        while(nodeBantu != NULL){
            if(nodeBantu->isidata.idKategori == IDCari){
                cout << "Data ID parent ditemukan pada list induk posisi ke-" << index << "!" << endl;
                cout << "ID : " << nodeBantu->isidata.idKategori << endl;
                cout << "Posisi dalam list induk : posisi ke-" << index << endl;
                cout << "Nama Kategori : " << nodeBantu->isidata.namaKategori << endl;
                ketemu = true;
                break;
            } else {
                nodeBantu = nodeBantu->next;
                index++;
            }
        }
        if(!ketemu){
            cout << "Data ID parent tidak ditemukan didalam list induk!" << endl;
        }
    }
}

void updateDataParentByID(listInduk &LInduk, string IDCari, string newNamaKategori) {
    if (isEmptyInduk(LInduk) == true) {
        cout << "List Induk kosong!" << endl;
    } else {
        NodeParent nodeBantu = LInduk.first;
        bool ketemu = false;
        while (nodeBantu != NULL) {
            if (nodeBantu->isidata.idKategori == IDCari) {
                // Proses Update
                nodeBantu->isidata.namaKategori = newNamaKategori;
                cout << "Update Parent Berhasil!" << endl;
                cout << "Node parent dengan ID " << IDCari << " berhasil diupdate menjadi : " << endl;
                cout << "Nama Kategori baru  : " << newNamaKategori << endl;
                ketemu = true;
                break; 
            } else {
                nodeBantu = nodeBantu->next;
            }
        }
        if (!ketemu) {
            cout << "Parent dengan ID " << IDCari << " tidak ditemukan" << endl;
        }
    }
}

//operasi pada child
void insertFirstChild(listAnak &LAnak, NodeChild nodeBaruChild) {
    if(isEmptyAnak(LAnak)) {
        LAnak.first = LAnak.last = nodeBaruChild;
    } else {
        nodeBaruChild->next = LAnak.first;
        LAnak.first->prev = nodeBaruChild;
        LAnak.first = nodeBaruChild;
    }
    cout << "Node child "<< nodeBaruChild->isidata.namaMakanan << " berhasil ditambahkan kedalam urutan pertama di list Anak!" << endl;
}

void insertLastChild(listAnak &LAnak, NodeChild nodeBaruChild) {
    if(isEmptyAnak(LAnak)) {
        LAnak.first = LAnak.last = nodeBaruChild;
    } else {
        nodeBaruChild->prev = LAnak.last;
        LAnak.last->next = nodeBaruChild;
        LAnak.last = nodeBaruChild;
    }
    cout << "Node child "<< nodeBaruChild->isidata.namaMakanan << " berhasil ditambahkan kedalam urutan terakhir di list Anak!" << endl;
}

void insertAfterChild(listAnak &LAnak, NodeChild nodeBaruChild, NodeChild nodePrevChild) {
    if(nodePrevChild == NULL) {
        cout << "Node Prev Parent tidak valid!" << endl;
    } else {
        if(nodePrevChild == LAnak.last){
            insertLastChild(LAnak, nodeBaruChild);
            return;
        } else {
            nodeBaruChild->next = nodePrevChild->next;
            nodeBaruChild->prev = nodePrevChild;
            (nodePrevChild->next)->prev = nodeBaruChild;
            nodePrevChild->next = nodeBaruChild;
            cout << "Node child "<< nodeBaruChild->isidata.namaMakanan << " berhasil ditambahkan kedalam list anak setelah node child "<< nodePrevChild->isidata.namaMakanan << endl;
        }
    }
}

void deleteFirstChild(listAnak &LAnak){
    if(isEmptyAnak(LAnak) == true){
        cout << "List anak kosong!" << endl;
    } else {
        NodeChild nodeHapus = LAnak.first;
        if (LAnak.first == LAnak.last) { // KASUS KHUSUS 1 ELEMEN
            LAnak.first = NULL;
            LAnak.last = NULL;
        } else {
            LAnak.first = LAnak.first->next;
            LAnak.first->prev = NULL;
            nodeHapus->next = NULL;
        }
        dealokasiNodeChild(nodeHapus);
        cout << "Node pertama list anak berhasil dihapus!" << endl;
    }
}

void deleteLastChild(listAnak &LAnak){
    if(isEmptyAnak(LAnak) == true){
        cout << "List anak kosong!" << endl;
    } else {
        NodeChild nodeHapus = LAnak.last;
        if (LAnak.first == LAnak.last) {
            LAnak.first = NULL;
            LAnak.last = NULL;
        } else {
            LAnak.last = LAnak.last->prev;
            nodeHapus->prev = NULL;
            LAnak.last->next = NULL;
        }
        dealokasiNodeChild(nodeHapus);
        cout << "Node terakhir list anak berhasil dihapus!" << endl;
    }
}

void deleteAfterChild(listAnak &LAnak, NodeChild nodePrev){
    if(isEmptyAnak(LAnak) == true){
        cout << "List induk kosong!" << endl;
    } else {
        if(nodePrev != NULL && nodePrev->next != NULL){
            NodeChild nodeHapus = nodePrev->next;
            nodePrev->next = nodeHapus->next;
            if (nodeHapus->next != NULL){
                (nodeHapus->next)->prev = nodePrev;
            } else {
                LAnak.last = nodePrev;
            }
            nodeHapus->next = NULL;
            dealokasiNodeChild(nodeHapus);
            cout << "Node child setelah node " << nodePrev->isidata.namaMakanan << " berhasil dihapus!" << endl;
        } else {
            cout << "Node prev tidak valid!" << endl;
        }
    }
}

void findChildByID(listInduk &LInduk, string IDCari){
    if(isEmptyInduk(LInduk) == true){
        cout << "List induk kosong!" << endl;
    } else {
        NodeParent nodeBantuParent = LInduk.first;
        int indexParent = 1;
        int ketemu = false;
        while(nodeBantuParent != NULL){
            NodeChild nodeBantuChild = nodeBantuParent->L_Anak.first;
            int indexChild = 1;
            while(nodeBantuChild != NULL){
                if(nodeBantuChild->isidata.idMakanan == IDCari) {
                    cout << "Data ID child ditemukan pada list anak dari node parent " << nodeBantuParent->isidata.namaKategori << " pada posisi ke-" << indexChild << "!" << endl;
                    cout << "--- Data Child ---" << endl;
                    cout << "ID Child : " << nodeBantuChild->isidata.idMakanan << endl;
                    cout << "Posisi dalam list anak : posisi ke-" << indexChild << endl;
                    cout << "Nama Makanan : " << nodeBantuChild->isidata.namaMakanan << endl;
                    cout << "Harga : " << nodeBantuChild->isidata.harga << endl;
                    cout << "---------------------------" << endl;
                    cout << "--- Data Parent ---" << endl;
                    cout << "ID Parent : " << nodeBantuParent->isidata.idKategori << endl;
                    cout << "Posisi dalam list induk : posisi ke-" << indexParent << endl;
                    cout << "Nama kategori : " << nodeBantuParent->isidata.namaKategori << endl;
                    ketemu = true;
                    break;
                } else {
                    nodeBantuChild = nodeBantuChild->next;
                    indexChild++;
                }
            }
            if(ketemu){
                break;
            } else {
                nodeBantuParent = nodeBantuParent->next;
                indexParent++;
            }
        }
        if(!ketemu){
            cout << "Data ID child tidak ditemukan didalam list anak!" << endl;
        }
    }
}

void updateDataChildByID(listInduk &LInduk, string IDCari, string newNamaMakanan, float newHarga) {
    if (isEmptyInduk(LInduk) == true) {
        cout << "List Induk kosong!" << endl;
    } else {
        NodeParent nodeBantuParent = LInduk.first;
        bool ketemu = false;
        // Loop Parent (karena child ada di dalam parent)
        while (nodeBantuParent != NULL) {
            NodeChild nodeBantuChild = nodeBantuParent->L_Anak.first;
            // Loop Child
            while (nodeBantuChild != NULL) {
                if (nodeBantuChild->isidata.idMakanan == IDCari) {
                    // Proses Update
                    nodeBantuChild->isidata.namaMakanan = newNamaMakanan;
                    nodeBantuChild->isidata.harga = newHarga;
                    cout << "Update Child Berhasil!" << endl;
                    cout << "Lokasi : Ada di dalam Parent " << nodeBantuParent->isidata.namaKategori << endl;
                    cout << "Node child dengan ID " << IDCari << " berhasil diupdate menjadi : " << endl;
                    cout << "Nama Makanan Baru  : " << newNamaMakanan << endl;
                    cout << "Harga Baru : " << newHarga << endl;
                    ketemu = true;
                    break; // Break loop child
                } else {
                    nodeBantuChild = nodeBantuChild->next;
                }
            }
            if (ketemu){
                break; // Break loop parent jika sudah ketemu di dalam
            } else {
                nodeBantuParent = nodeBantuParent->next;
            }
        }
        if (!ketemu) {
            cout << "Child dengan ID " << IDCari << " tidak ditemukan di parent manapun." << endl;
        }
    }
}

//operasi print
void printStrukturMLL(listInduk &LInduk) {
    if(isEmptyInduk(LInduk)) {
        cout << "List induk kosong!" << endl;
    } else {
        NodeParent nodeBantuParent = LInduk.first;
        int indexParent = 1;
        while(nodeBantuParent != NULL) {
            cout << "=== Parent " << indexParent << " ===" << endl;
            cout << "ID Kategori : " << nodeBantuParent->isidata.idKategori << endl;
            cout << "Nama Kategori : " << nodeBantuParent->isidata.namaKategori << endl;

            //print list anak dari node parentnya
            NodeChild nodeBantuChild = nodeBantuParent->L_Anak.first;
            if(nodeBantuChild == NULL) {
                cout << "  (tidak ada child)" << endl;
            } else {
                int indexChild = 1;
                while(nodeBantuChild != NULL) {
                    cout << "  - Child " << indexChild << " :" << endl;
                    cout << "      ID Makanan : " << nodeBantuChild->isidata.idMakanan << endl;
                    cout << "      Nama Makanan : " << nodeBantuChild->isidata.namaMakanan << endl;
                    cout << "      Harga : " << nodeBantuChild->isidata.harga << endl;
                    nodeBantuChild = nodeBantuChild->next;
                    indexChild++;
                }
            }
            cout << "---------------------------" << endl;
            nodeBantuParent = nodeBantuParent->next;
            indexParent++;
        }
    }
}

void printListInduk(listInduk &LInduk) {
    if(isEmptyInduk(LInduk)) {
        cout << "List induk Kosong!" << endl;
    } else {
        NodeParent nodeBantuParent = LInduk.first;
        int index = 1;
        while(nodeBantuParent != NULL) {
            cout << "=== Parent " << index << " ===" << endl;
            cout << "ID Kategori : " << nodeBantuParent->isidata.idKategori << endl;
            cout << "Nama Kategori : " << nodeBantuParent->isidata.namaKategori << endl;
            cout << "---------------------------" << endl;
            nodeBantuParent = nodeBantuParent->next;
            index++;
        }
    }
}

void printListAnak(listInduk &LInduk, NodeParent nodeInduk) {
    if(isEmptyInduk(LInduk) == true || nodeInduk == NULL){
        cout << "List induk kosong atau node induk tidak valid!" << endl;
    } else {
        NodeChild nodeBantuChild = nodeInduk->L_Anak.first;
        if(nodeBantuChild == NULL) {
            cout << "node parent " << nodeInduk->isidata.namaKategori << " tidak memiliki list anak!" << endl;
        } else {
            cout << "=== List Anak Node Parent " << nodeInduk->isidata.namaKategori << " ===" << endl;
            int index = 1;
            while(nodeBantuChild != NULL) {
                cout << "Child " << index << " :" << endl;
                cout << "ID Makanan : " << nodeBantuChild->isidata.idMakanan << endl;
                cout << "Nama Makanan : " << nodeBantuChild->isidata.namaMakanan << endl;
                cout << "Harga : " << nodeBantuChild->isidata.harga << endl;
                cout << "---------------------------" << endl;
                nodeBantuChild = nodeBantuChild->next;
                index++;
            }
        }
    }
}

//operasi hapus list
void hapusListInduk(listInduk &LInduk) {
    NodeParent nodeBantu = LInduk.first;
    while(nodeBantu != NULL) {
        NodeParent nodeHapus = nodeBantu;
        nodeBantu = nodeBantu->next;
        //panggil prosedur hapusListAnak() untuk menghapus child-child nya
        hapusListAnak(nodeHapus->L_Anak);
        dealokasiNodeParent(nodeHapus);
    }
    LInduk.first = LInduk.last = NULL;
}

void hapusListAnak(listAnak &LAnak) {
    NodeChild nodeBantu = LAnak.first;
    while(nodeBantu != NULL) {
        NodeChild nodeHapus = nodeBantu;
        nodeBantu = nodeBantu->next;
        dealokasiNodeChild(nodeHapus);
    }
    LAnak.first = LAnak.last = NULL;
}

```
### main.cpp
```c++
#include "mll.h"
#include "mll.cpp"
#include <iostream>

using namespace std;

int main() {
    // 1. Inisialisasi List
    listInduk L;
    createListInduk(L);
    cout << "=== MENU RESTORAN DIBUAT ===" << endl << endl;

    // 2. Membuat Data Parent (Kategori Makanan)
    // Kita simpan pointer-nya agar mudah memasukkan anak nanti
    NodeParent Kat1 = alokasiNodeParent("K01", "Makanan Berat");
    insertFirstParent(L, Kat1);

    NodeParent Kat2 = alokasiNodeParent("K02", "Minuman");
    insertAfterParent(L, Kat2, Kat1);

    NodeParent Kat3 = alokasiNodeParent("K03", "Dessert");
    insertLastParent(L, Kat3);
    
    cout << endl;

    // 3. Memasukkan Data Child (Menu Makanan) ke Kategori Tertentu
    
    // --> Isi Kategori Makanan Berat (K01)
    NodeChild Mkn1 = alokasiNodeChild("M01", "Nasi Goreng Spesial", 25000);
    insertFirstChild(Kat1->L_Anak, Mkn1);

    NodeChild Mkn2 = alokasiNodeChild("M02", "Ayam Bakar Madu", 30000);
    insertLastChild(Kat1->L_Anak, Mkn2);

    // --> Isi Kategori Minuman (K02)
    NodeChild Min1 = alokasiNodeChild("D01", "Es Teh Manis", 5000);
    insertLastChild(Kat2->L_Anak, Min1);
    
    NodeChild Min2 = alokasiNodeChild("D02", "Jus Alpukat", 15000);
    insertFirstChild(Kat2->L_Anak, Min2);

    // --> Isi Kategori Dessert (K03)
    NodeChild Des1 = alokasiNodeChild("S01", "Puding Coklat", 10000);
    insertLastChild(Kat3->L_Anak, Des1);
    cout << endl;

    cout << "=== TAMPILAN AWAL MENU ===" << endl;
    printStrukturMLL(L);
    cout << endl;

    // 4. Test Pencarian (Find)
    cout << "=== TEST PENCARIAN ===" << endl;
    findParentByID(L, "K02"); // Cari Kategori Minuman
    cout << "---------------------------" << endl;
    findChildByID(L, "M01");  // Cari Nasi Goreng
    cout << "---------------------------" << endl;
    findChildByID(L, "X99");  // Cari data ngawur (harus not found)
    cout << "---------------------------" << endl;
    cout << endl;

    // 5. Test Update Data
    cout << "=== TEST UPDATE ===" << endl;
    // Update Nama Kategori (Parent)
    // Mengubah "Dessert" menjadi "Makanan Penutup"
    updateDataParentByID(L, "K03", "Makanan Penutup");
    cout << "---------------------------" << endl;
    
    // Update Data Makanan (Child)
    // Mengubah "Nasi Goreng Spesial" jadi "Nasgor Gila", harga naik jadi 28000
    updateDataChildByID(L, "M01", "Nasgor Gila", 28000);
    cout << "---------------------------" << endl;
    
    cout << "\n=== SETELAH UPDATE ===" << endl;
    // Kita cek apakah data berubah
    printListInduk(L); // Cek nama kategori saja
    cout << endl;
    printListAnak(L, Kat1); // Cek list anak di kategori 1
    cout << endl;

    // 6. Test Penghapusan (Delete)
    cout << "=== TEST DELETE ===" << endl;
    
    // Hapus Child: Hapus Jus Alpukat (D02) dari Minuman
    cout << "> Menghapus Child D02..." << endl;
    deleteFirstChild(Kat2->L_Anak); 
    
    // Hapus Parent: Hapus Kategori Dessert/Makanan Penutup (K03)
    // DeleteLastParent akan menghapus elemen terakhir (K03)
    cout << "> Menghapus Parent Terakhir (K03)..." << endl;
    deleteLastParent(L); 

    cout << "\n=== TAMPILAN AKHIR MENU ===" << endl;
    printStrukturMLL(L);

    return 0;
}
   
   
```


## Unguided 

### 1. [main2.cpp]

```C++
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

}

```
Program ini membuat multi linked list dengan beberapa simpul induk dan anak, lalu menampilkan semua data beserta hubungannya.
#### Full code Screenshot:
<img width="580" height="430" alt="image" src="https://github.com/user-attachments/assets/145e5f31-d365-4ddb-bce6-7f6e66b3db66" />

### [multilist2.cpp]

```C++
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

```

Kode ini mengelola multi linked list dengan berbagai operasi dasar. Di dalamnya terdapat fungsi untuk membuat dan menghapus simpul induk maupun anak, menambahkan simpul induk di awal, akhir, atau setelah simpul tertentu, serta menambahkan simpul anak di akhir list anak. Selain itu, kode ini juga bisa menampilkan seluruh isi multi linked list beserta hubungan antara induk dan anak-anaknya. Dengan demikian, struktur data ini memudahkan pengelolaan data yang memiliki hubungan hirarkis.
#### Full code Screenshot:
<img width="333" height="596" alt="image" src="https://github.com/user-attachments/assets/d42e7a3e-b930-43c4-a721-f3863fdbf66e" />
<img width="498" height="485" alt="image" src="https://github.com/user-attachments/assets/66d4684f-a934-4533-b5de-2d7c878b1858" />



### [multilist2.h]

```C++
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

```

#### Output:
<img width="284" height="76" alt="image" src="https://github.com/user-attachments/assets/0c5199df-a829-4234-9158-b9fc555a5fc9" />

Header ini mendefinisikan multi linked list dengan simpul induk dan anak, beserta fungsi untuk membuat, menambah, menghapus, dan menampilkan hubungan antara induk dan anak.
#### Full code Screenshot:
<img width="254" height="526" alt="image" src="https://github.com/user-attachments/assets/80ab20cb-142b-4faf-89ad-a09b80daeeb6" />

### 2. [main.cpp]

```C++
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

```
Program ini mengelola **circular linked list**, menambahkan simpul di awal, akhir, atau setelah simpul tertentu, lalu menampilkan seluruh isi list sesuai urutan penyisipannya.
#### Full code Screenshot:
<img width="315" height="522" alt="image" src="https://github.com/user-attachments/assets/b4aa3bd9-eef6-44c1-8162-17e6d4132082" />

### [circularlist1.cpp]

```C++
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

```

Program ini menangani circular linked list, termasuk membuat dan menghapus simpul, menambahkan simpul di posisi tertentu, mencari simpul dengan NIM tertentu, dan menampilkan seluruh isi list.
#### Full code Screenshot:
<img width="456" height="575" alt="image" src="https://github.com/user-attachments/assets/521bb63a-2dc3-408e-a19e-2a0ad1ace30f" />
<img width="356" height="276" alt="image" src="https://github.com/user-attachments/assets/f43325b5-f16b-47a8-bf57-f8380ea24662" />


### [circularlist1.h]

```C++
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

```

#### Output:
<img width="450" height="467" alt="image" src="https://github.com/user-attachments/assets/a6830d0a-f9c9-4499-8d36-c1cf2e155588" />

Header ini mendefinisikan circular linked list untuk data mahasiswa, termasuk struktur simpul (ElmNode) dan list itu sendiri. Di dalamnya terdapat deklarasi fungsi untuk membuat dan menghapus simpul, menambahkan simpul di awal, akhir, atau setelah simpul tertentu, menghapus simpul dari posisi tertentu, mencari simpul berdasarkan data, serta menampilkan seluruh isi list.
#### Full code Screenshot:
<img width="430" height="462" alt="image" src="https://github.com/user-attachments/assets/b04138f1-8abd-4008-a9ed-61f4670f5278" />

## Kesimpulan
MLL efektif untuk mengelola data yang berhubungan secara hierarkis, sedangkan CDLL memudahkan pengelolaan data yang terhubung secara melingkar dengan akses dua arah.
## Referensi
[1] Knuth, D. E. (1997). The Art of Computer Programming, Volume 1: Fundamental Algorithms (3rd ed.). Addison-Wesley.
[2] Horowitz, E., Sahni, S., & Rajasekaran, S. (2008). Fundamentals of Data Structures in C++ (2nd ed.). Silicon Press.
[3] Langsam, Y., Augenstein, M., & Tenenbaum, A. (2007). Data Structures Using C and C++ (2nd ed.). Prentice Hall.
[4] Lafore, R. (2002). Data Structures and Algorithms in C++ (2nd ed.). Sams Publishing.
