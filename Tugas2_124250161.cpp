#include <iostream>
#include <string>
#include <vector>

using namespace std;

//struktur Data Kendaraan
class Kendaraan {
public:
    string nopol;
    string nama;
    string status;

    Kendaraan() {}
    Kendaraan(string np, string nm) {
        nopol = np;
        nama = nm;
        status = "Di Luar Parkiran"; //status awal otomatis
    }
};

//pohon biner
struct NodePTB {
    Kendaraan kendaraan;
    NodePTB* left;
    NodePTB* right;

    NodePTB(Kendaraan k) {
        kendaraan = k;
        left = nullptr;
        right = nullptr;
    }
};

class PTB {
public:
    NodePTB* root;

    PTB() {
        root = nullptr;
    }

    NodePTB* insert(NodePTB* node, Kendaraan k) {
        if (node == nullptr) {
            return new NodePTB(k);
        }
        if (k.nopol < node->kendaraan.nopol) {
            node->left = insert(node->left, k);
        } else if (k.nopol > node->kendaraan.nopol) {
            node->right = insert(node->right, k);
        }
        return node;
    }

    NodePTB* search(NodePTB* node, string nopol) {
        if (node == nullptr || node->kendaraan.nopol == nopol) {
            return node;
        }
        if (node->kendaraan.nopol < nopol) {
            return search(node->right, nopol);
        }
        return search(node->left, nopol);
    }
    void inorder(NodePTB* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << "Nopol: " << node->kendaraan.nopol 
                 << " | Pemilik: " << node->kendaraan.nama 
                 << " | Status: " << node->kendaraan.status << endl;
            inorder(node->right);
        }
    }
    NodePTB* minValueNode(NodePTB* node) {
        NodePTB* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    NodePTB* deleteNode(NodePTB* root, string nopol, bool& isDeleted) {
        if (root == nullptr) return root;

        if (nopol < root->kendaraan.nopol) {
            root->left = deleteNode(root->left, nopol, isDeleted);
        } else if (nopol > root->kendaraan.nopol) {
            root->right = deleteNode(root->right, nopol, isDeleted);
        } else {
            isDeleted = true;
            if (root->left == nullptr) {
                NodePTB* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                NodePTB* temp = root->left;
                delete root;
                return temp;
            }
            NodePTB* temp = minValueNode(root->right);
            root->kendaraan = temp->kendaraan;
            root->right = deleteNode(root->right, temp->kendaraan.nopol, isDeleted);
        }
        return root;
    }
};

// stuck
struct RiwayatAksi {
    string aksi;
    string nopol;
};
class StackUndo {
private:
    vector<RiwayatAksi> items;
public:
    void push(string aksi, string nopol) {
        items.push_back({aksi, nopol});
    }

    RiwayatAksi pop() {
        if (items.empty()) return {"", ""};
        RiwayatAksi r = items.back();
        items.pop_back();
        return r;
    }

    bool isEmpty() {
        return items.empty();
    }
};

//queue
class QueueAntrian {
private:
    vector<string> items;
public:
    void enqueue(string nopol) {
        items.push_back(nopol);
    }

    string dequeue() {
        if (items.empty()) return "";
        string front = items.front();
        items.erase(items.begin());
        return front;
    }

    bool isEmpty() {
        return items.empty();
    }
    void display() {
        if (items.empty()) {
            cout << "Antrian kosong\n";
        } else {
            for (string nopol : items) {
                cout << nopol << " menunggu giliran masuk parkiran\n";
            }
        }
    }
};
// kelas utama sitem
class SistemParkir {
public:
    PTB ptb;
    StackUndo stack;
    QueueAntrian queue;
    int kapasitas;
    int jumlah_parkir;

    SistemParkir(int cap) {
        kapasitas = cap;
        jumlah_parkir = 0;
    }

    void tambahKendaraan(string nopol, string nama) {
        Kendaraan k(nopol, nama);
        ptb.root = ptb.insert(ptb.root, k);
        cout << "Data kendaraan berhasil ditambahkan\n";
    }

    void tampilkanKendaraan() {
        cout << "\n--- Daftar Semua Kendaraan ---\n";
        if (ptb.root == nullptr) {
            cout << "Belum ada data kendaraan.\n";
        } else {
            ptb.inorder(ptb.root);
        }
    }

    void catatMasuk(string nopol) {
        NodePTB* node = ptb.search(ptb.root, nopol);
        if (node != nullptr) {
            if (node->kendaraan.status == "Di Luar Parkiran") {
                if (jumlah_parkir < kapasitas) {
                    node->kendaraan.status = "Di Parkiran";
                    jumlah_parkir++;
                    stack.push("MASUK", nopol);
                    cout << "Kendaraan berhasil masuk\n";
                } else {
                    queue.enqueue(nopol);
                    cout << "Parkiran penuh, kendaraan masuk ke dalam antrian\n";
                }
            } else {
                cout << "Kendaraan sudah berada di dalam parkiran.\n";
            }
        } else {
            cout << "Kendaraan tidak ditemukan!\n";
        }
    }

    void catatKeluar(string nopol) {
        NodePTB* node = ptb.search(ptb.root, nopol);
        if (node != nullptr && node->kendaraan.status == "Di Parkiran") {
            node->kendaraan.status = "Di Luar Parkiran";
            jumlah_parkir--;
            stack.push("KELUAR", nopol);
            cout << "Kendaraan berhasil keluar\n";
            // cek misal ada antrian
            if (!queue.isEmpty()) {
                string nopol_antrian = queue.dequeue();
                NodePTB* node_antrian = ptb.search(ptb.root, nopol_antrian);
                if (node_antrian != nullptr) {
                    node_antrian->kendaraan.status = "Di Parkiran";
                    jumlah_parkir++;
                    stack.push("MASUK", nopol_antrian);
                    cout << "Kendaraan berikutnya langsung masuk ke area parkir dari antrian\n";
                }
            }
        } else {
            cout << "Kendaraan tidak ditemukan atau tidak berada di dalam parkiran!\n";
        }
    }

    void hapusKendaraan(string nopol) {
        bool isDeleted = false;
        ptb.root = ptb.deleteNode(ptb.root, nopol, isDeleted);
        if (isDeleted) {
            cout << "Data kendaraan berhasil dihapus\n";
        } else {
            cout << "Kendaraan tidak ditemukan!\n";
        }
    }
    void undoAksi() {
        RiwayatAksi aksi_terakhir = stack.pop();
        if (aksi_terakhir.aksi != "") {
            NodePTB* node = ptb.search(ptb.root, aksi_terakhir.nopol);
            if (node != nullptr) {
                if (aksi_terakhir.aksi == "MASUK") {
                    node->kendaraan.status = "Di Luar Parkiran";
                    jumlah_parkir--;
                    cout << "Undo: Kendaraan keluar dari parkiran\n";
                } else if (aksi_terakhir.aksi == "KELUAR") {
                    node->kendaraan.status = "Di Parkiran";
                    jumlah_parkir++;
                    cout << "Undo: Kendaraan masuk kembali ke parkiran\n";
                }
            }
        } else {
            cout << "Tidak ada aksi untuk di-undo\n";
        }
    }

    void tampilkanAntrian() {
        cout << "\n--- Antrian Parkir ---\n";
        queue.display();
    }
};

// main progrsm
int main() {
    int kapasitas_parkir = 3; 
    SistemParkir sistem(kapasitas_parkir);
    int pilihan;
    string nopol, nama;

    while (true) {
        cout << "\n=== SISTEM PARKIR BANDARA GSA ===\n";
        cout << "1. Tambah Data Kendaraan\n";
        cout << "2. Tampil Semua Kendaraan\n";
        cout << "3. Catat Kendaraan Masuk\n";
        cout << "4. Catat Kendaraan Keluar\n";
        cout << "5. Hapus Data Kendaraan\n";
        cout << "6. Undo Aksi Terakhir\n";
        cout << "7. Tampilkan Antrian Parkir\n";
        cout << "8. Keluar\n";
        cout << "Pilih menu (1-8): ";
        cin >> pilihan;
        cin.ignore(); //membersihkan sisa newline di buffer input

        if (pilihan == 1) {
            cout << "Masukkan Nomor Polisi (cth: B 1234 ABC): ";
            getline(cin, nopol);
            cout << "Masukkan Nama Pemilik: ";
            getline(cin, nama);
            sistem.tambahKendaraan(nopol, nama);
        } 
        else if (pilihan == 2) {
            sistem.tampilkanKendaraan();
        } 
        else if (pilihan == 3) {
            cout << "Masukkan Nomor Polisi Kendaraan Masuk: ";
            getline(cin, nopol);
            sistem.catatMasuk(nopol);
        } 
        else if (pilihan == 4) {
            cout << "Masukkan Nomor Polisi Kendaraan Keluar: ";
            getline(cin, nopol);
            sistem.catatKeluar(nopol);
        } 
        else if (pilihan == 5) {
            cout << "Masukkan Nomor Polisi yang akan dihapus: ";
            getline(cin, nopol);
            sistem.hapusKendaraan(nopol);
        } 
        else if (pilihan == 6) {
            sistem.undoAksi();
        } 
        else if (pilihan == 7) {
            sistem.tampilkanAntrian();
        } 
        else if (pilihan == 8) {
            cout << "Keluar dari sistem. Terima kasih!\n";
            break;
        } 
        else {
            cout << "Pilihan tidak valid!\n";
        }
    }

    return 0;
}
