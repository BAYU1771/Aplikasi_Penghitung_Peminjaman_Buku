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

void tambahBuku();
void pinjamBuku();
void kembalikanBuku();
void tampilkanBuku();
int hitungDendaTerlambat(time_t tanggalKembali);
string formatTanggal(time_t tanggal);

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
                tambahBuku();
                break;
            case 2:
                pinjamBuku();
                break;
            case 3:
                kembalikanBuku();
                break;
            case 4:
                tampilkanBuku();
                break;
            case 5:
                cout << "Terima Kasih Telah Berkunjung\n";
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

void kembalikanBuku() {
    string judul;
    cout << "Masukkan judul buku yang ingin dikembalikan: ";
    cin.ignore(); // Membersihkan buffer input
    getline(cin, judul);

    for (Buku& buku : buku) {
        if (buku.judul == judul && buku.sedangDipinjam) {
            time_t sekarang;
            time(&sekarang);
            buku.sedangDipinjam = false;

            int dendaTerlambat = hitungDendaTerlambat(buku.tanggalKembali);
            if (dendaTerlambat > 0) {
                cout << "Anda terlambat mengembalikan buku. Denda: Rp" << dendaTerlambat << endl;
            } else {
                cout << "Buku berhasil dikembalikan tepat waktu.\n";
            }
            return;
        }
    }
    cout << "Buku tidak ditemukan atau belum dipinjam.\n";
}

void tampilkanBuku() {
    cout << "\n===== Daftar Buku =====\n";
    for (const Buku& buku : buku) {
        cout << "Judul: " << buku.judul << endl;
        if (buku.sedangDipinjam) {
            cout << "Status: Dipinjam\n";
            cout << "Tanggal Pengembalian: " << formatTanggal(buku.tanggalKembali) << endl;
        } else {
            cout << "Status: Tersedia\n";
        }
        cout << "--------------------------\n";
    }
}

int hitungDendaTerlambat(time_t tanggalKembali) {
    time_t sekarang;
    time(&sekarang);
    double detikTerlambat = difftime(sekarang, tanggalKembali);
    if (detikTerlambat > 0) {
        int hariTerlambat = detikTerlambat / (24 * 60 * 60);
        return hariTerlambat * DENDA_TERLAMBAT;
    }
    return 0;
}

string formatTanggal(time_t tanggal) {
    struct tm* infoWaktu = localtime(&tanggal);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%d-%m-%Y", infoWaktu);
    return string(buffer);
}


