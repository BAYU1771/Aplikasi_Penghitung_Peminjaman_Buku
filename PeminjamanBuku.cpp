#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

struct Buku {
    string judul;
    time_t tanggalPinjam;
    time_t tanggalKembali;
    bool sedangDipinjam;
};

vector<Buku> buku;
const int MAKS_HARI_PINJAM = 7;
const int DENDA_TERLAMBAT = 2000;

int main() {
    int pilihan;
    do {
        cout << "\n===== Menu =====\n";
        cout << "1. Tambah Buku\n";
        cout << "2. Pinjam Buku\n";
        cout << "3. Kembalikan Buku\n";
        cout << "4. Tampilkan Daftar Buku\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                
                break;
            case 2:
                
                break;
            case 3:
                
                break;
            case 4:
                
                break;
            case 5:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Coba lagi.\n";
        }
    } while (pilihan != 5);

    return 0;
}

void tambahBuku() {
    Buku bukuBaru;
    cout << "Masukkan judul buku: ";
    cin.ignore();
    getline(cin, bukuBaru.judul);
    bukuBaru.sedangDipinjam = false;
    buku.push_back(bukuBaru);
    cout << "Buku berhasil ditambahkan.\n";
}

void pinjamBuku() {
    string judul;
    cout << "Masukkan judul buku yang ingin dipinjam: ";
    cin.ignore(); // Membersihkan buffer input
    getline(cin, judul);

    for (Buku& buku : buku) {
        if (buku.judul == judul && !buku.sedangDipinjam) {
            buku.sedangDipinjam = true;
            time(&buku.tanggalPinjam);
            buku.tanggalKembali = buku.tanggalPinjam + MAKS_HARI_PINJAM * 24 * 60 * 60;
            cout << "Buku berhasil dipinjam. Tanggal pengembalian: " << formatTanggal(buku.tanggalKembali) << endl;
            return;
        }
    }
    cout << "Buku tidak ditemukan atau sedang dipinjam.\n";
}

