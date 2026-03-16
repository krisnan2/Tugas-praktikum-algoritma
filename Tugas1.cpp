#include <iostream>
#include <cstdio>
#include <cstring>
#include <iomanip>
using namespace std;

struct Product {
    char name[60];
    char category[30];
    double price;
    int stock;
    float rating;
};

Product katalog[100];
int jumlahProduk = 0;
const char* filename = "shopease_db.txt";


// ================= LOAD DATA =================
void loadData() {
    FILE* pf = fopen(filename, "r");

    if (pf == NULL) return;

    jumlahProduk = 0;

    while (fscanf(pf, " %[^|]|%[^|]|%lf|%d|%f\n",
                  katalog[jumlahProduk].name,
                  katalog[jumlahProduk].category,
                  &katalog[jumlahProduk].price,
                  &katalog[jumlahProduk].stock,
                  &katalog[jumlahProduk].rating) != EOF) {
        jumlahProduk++;
    }

    fclose(pf);
}
// ================= SAVE DATA =================
void saveData() {
    FILE* pf = fopen(filename, "w");
if (pf == NULL) {
        cout << "\n[GAGAL] File tidak dapat dibuka!\n";
        return;
    }
    for (int i = 0; i < jumlahProduk; i++) {
        fprintf(pf, "%s|%s|%.0lf|%d|%.1f\n",
                katalog[i].name,
                katalog[i].category,
                katalog[i].price,
                katalog[i].stock,
                katalog[i].rating);}
         fclose(pf);
}

// ================= BUBBLE SORT =================
void bubbleSortAscendingByName() {
    for (int i = 0; i < jumlahProduk - 1; i++) {
        for (int j = 0; j < jumlahProduk - i - 1; j++) {
            if (strcmp(katalog[j].name, katalog[j + 1].name) > 0) {
                Product temp = katalog[j];
                katalog[j] = katalog[j + 1];
                katalog[j + 1] = temp;
            }
        }
    }
}
// ================= QUICK SORT =================
int partition(int low, int high) {
    float pivot = katalog[high].rating;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (katalog[j].rating > pivot) {
            i++;
            Product temp = katalog[i];
            katalog[i] = katalog[j];
            katalog[j] = temp;
        }
    }
    Product temp = katalog[i + 1];
    katalog[i + 1] = katalog[high];
    katalog[high] = temp;

    return i + 1;
}

void quickSortDescendingByRating(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        quickSortDescendingByRating(low, pi - 1);
        quickSortDescendingByRating(pi + 1, high);
    }
}
// ================= TAMPILKAN TABEL =================
void tampilkanTabel() {
    cout << "\n=================================================================================================\n";
    cout << left << setw(30) << "Nama Produk"
         << setw(20) << "Kategori"
         << setw(20) << "Harga (Rp)"
         << setw(10) << "Stok"
         << setw(10) << "Rating" << endl;
    cout << "=================================================================================================\n";
    for (int i = 0; i < jumlahProduk; i++) {
        cout << left << setw(30) << katalog[i].name
             << setw(20) << katalog[i].category
             << setw(20) << fixed << setprecision(0) << katalog[i].price
             << setw(10) << katalog[i].stock
             << setw(10) << fixed << setprecision(1) << katalog[i].rating << endl;
    }
    cout << "=================================================================================================\n";}
// ================= TAMBAH PRODUK =================
void tambahProduk() {
    int jumlahTambah;
    cout << "\n--- Tambah Produk Baru ---\n";
    cout << "Berapa banyak produk yang ingin ditambahkan? ";
    cin >> jumlahTambah;
    if (jumlahTambah <= 0) {
        cout << "\n[GAGAL] Jumlah produk harus lebih dari 0!\n";
        return;
    }if (jumlahProduk + jumlahTambah > 100) {
        cout << "\n[GAGAL] Kapasitas katalog penuh!\n";
        return;
    }cin.ignore();
    for (int i = 0; i < jumlahTambah; i++) {
        cout << "\nData Produk ke-" << jumlahProduk + 1 << endl;
        cout << "Nama Produk : ";
        cin.getline(katalog[jumlahProduk].name, 60);
        cout << "Kategori    : ";
        cin.getline(katalog[jumlahProduk].category, 30);
        do {
            cout << "Harga       : ";
            cin >> katalog[jumlahProduk].price;
        } while (katalog[jumlahProduk].price < 0);
        do {
            cout << "Stok        : ";
            cin >> katalog[jumlahProduk].stock;
        } while (katalog[jumlahProduk].stock < 0);
        do {
            cout << "Rating (0-5): ";
            cin >> katalog[jumlahProduk].rating;
        } while (katalog[jumlahProduk].rating < 0 || katalog[jumlahProduk].rating > 5);

        cin.ignore();
        jumlahProduk++;}
    saveData();
    cout << "\n[BERHASIL] Produk berhasil ditambahkan dan disimpan!\n";
}
// ================= TAMPILKAN PRODUK =================
void tampilkanDaftarProduk() {
    if (jumlahProduk == 0) {
        cout << "\nKatalog masih kosong!\n";
        return;}
    int mode;
    cout << "\n--- Mode Tampilan ---\n";
    cout << "1. Urutkan berdasarkan Nama (Ascending)\n";
    cout << "2. Urutkan berdasarkan Rating (Descending)\n";
    cout << "Pilih mode: ";
    cin >> mode;
    if (mode == 1) {
        bubbleSortAscendingByName();
    } else if (mode == 2) {
        quickSortDescendingByRating(0, jumlahProduk - 1);
    } else {
        cout << "\nPilihan tidak valid!\n";
        return;
    }
    tampilkanTabel();
}
// ================= SEARCHING =================
void cariProduk() {
    if (jumlahProduk == 0) {
        cout << "\nKatalog masih kosong!\n";
        return;
    }
    cin.ignore();

    char keyword[60];
    bool ditemukan = false;
    cout << "\nMasukkan Nama Produk: ";
    cin.getline(keyword, 60);
    for (int i = 0; i < jumlahProduk; i++) {
        if (strcmp(katalog[i].name, keyword) == 0) {
            cout << "\n[PRODUK DITEMUKAN]\n";
            cout << "Nama Produk : " << katalog[i].name << endl;
            cout << "Kategori    : " << katalog[i].category << endl;
            cout << "Harga       : Rp " << fixed << setprecision(0) << katalog[i].price << endl;
            cout << "Stok        : " << katalog[i].stock << endl;
            cout << "Rating      : " << fixed << setprecision(1) << katalog[i].rating << endl;
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "\nProduk tidak ditemukan!\n";
    }
}
int main() {
    int pilihan;
    loadData();
    do {
        cout << "\n=====================================\n";
        cout << "   SISTEM MANAJEMEN KATALOG SHOPEASE\n";
        cout << "=====================================\n";
        cout << "1. Tambah Produk Baru\n";
        cout << "2. Tampilkan Daftar Produk\n";
        cout << "3. Cari Produk\n";
        cout << "4. Keluar dan Simpan\n";
        cout << "Pilih menu (1-4): ";
        cin >> pilihan;
        switch (pilihan) {
            case 1:
                tambahProduk();
                break;
            case 2:
                tampilkanDaftarProduk();
                break;
            case 3:
                cariProduk();
                break;
            case 4:
                saveData();
                cout << "\nTerima kasih telah menggunakan program ini.\n";
                break;
            default:
                cout << "\nPilihan tidak valid!\n";
        }

    } while (pilihan != 4);

    return 0;
}
