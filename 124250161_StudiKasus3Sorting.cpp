#include <iostream>
#include <string>
using namespace std;
void bubbleSortAscending(string arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            //membandingkan elemen saat ini dengan elemen berikutnya 
            //karena ascending, jika elemen di kiri lebih besar dari yang di kanan, maka tukar posisiny
            if (arr[j] > arr[j + 1]) {
                string temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void quickSortDescending(string arr[], int awal, int akhir) {
    int low = awal, high = akhir;
    //memilih pivot menggunakan pendekatan divide and conquer, di sini dari elemen tengah array
    string pivot = arr[(awal + akhir) / 2];
    //mempartisi array menjadi dua bagian berdasarkan nilai pivot
    do {
        //modifikasi untuk Descending: 
        //cari elemen di kiri yang lebih kecil dari pivot, dan di kanan yang lebih besar dari pivot
        while (arr[low] > pivot) low++;
        while (arr[high] < pivot) high--;

        //tukar posisi kalo ditemukan elemen yang salah tempat (tidak sesuai urutan)
        if (low <= high) {
            string temp = arr[low];
            arr[low] = arr[high];
            arr[high] = temp;
            low++;
            high--;
        }
    } while (low <= high);

    //buat nerapin rekursi untuk mengurutkan sisa sub-array di bagian kiri dan kanan pivot
    if (awal < high) quickSortDescending(arr, awal, high);
    if (low < akhir) quickSortDescending(arr, low, akhir);
}

int main() {
    int n;
    cout << "Masukkan jumlah mahasiswa: ";
    cin >> n;
    cin.ignore(); 

    string namaMahasiswa[n]; 
    string copyNama[n];      

    cout << "Masukkan nama-nama mahasiswa:\n";
    for (int i = 0; i < n; i++) {
        cout << "Nama mahasiswa ke-" << (i + 1) << ": ";
        getline(cin, namaMahasiswa[i]); 
        //mnyimpan salinan data input awal ke array lain untuk digunakan pada Quick Sort nanti
        copyNama[i] = namaMahasiswa[i]; 
    }
    cout << "\n========================================\n";
    //mengeksekusi Bubble Sort pada array namaMahasiswa
    bubbleSortAscending(namaMahasiswa, n);
    
    cout << "Hasil Pengurutan Ascending (Bubble Sort):\n";
    for (int i = 0; i < n; i++) {
        cout << "- " << namaMahasiswa[i] << endl;
    }
    cout << "\n----------------------------------------\n";
    //mengeksekusi Quick Sort pada array copyNama agar data yang diproses masih sesuai urutan input asli
    quickSortDescending(copyNama, 0, n - 1);
    cout << "Hasil Pengurutan Descending (Quick Sort):\n";
    for (int i = 0; i < n; i++) {
        cout << "- " << copyNama[i] << endl;
    }
    cout << "========================================\n";
    return 0;
}
