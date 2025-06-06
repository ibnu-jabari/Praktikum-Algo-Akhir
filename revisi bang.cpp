#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Habit {
    string nama;
    string tanggal;
    string status;
    int id;
    Habit* next;
};

Habit* head = nullptr;
int habitCounter = 1;

void tambahHabit(string nama, string tanggal, string status) {
    if (nama.empty() || tanggal.empty() || (status != "sudah" && status != "belum")) {
        cout << "Input tidak valid. Nama, tanggal tidak boleh kosong dan status hanya boleh 'sudah' atau 'belum'.\n";
        return;
    }

    Habit* baru = new Habit{nama, tanggal, status, habitCounter++, nullptr};
    if (!head) {
        head = baru;
        cout << "Habit baru ditambahkan sebagai data pertama.\n";
    } else {
        Habit* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = baru;
        cout << "Habit berhasil ditambahkan.\n";
    }
}

void tampilkanHabit() {
    if (!head) {
        cout << "Belum ada data habit.\n";
        return;
    }
    Habit* bantu = head;
    cout << "\nDaftar Habit:\n";
    while (bantu) {
        cout << bantu->id << ". " << bantu->nama << " | " << bantu->tanggal << " | " << bantu->status << endl;
        bantu = bantu->next;
    }
}

void cariHabit(string kataCari) {
    Habit* bantu = head;
    bool ditemukan = false;
    while (bantu) {
        if (bantu->nama.find(kataCari) != -1) {
            cout << "Ditemukan: " << bantu->id << ". " << bantu->nama << " | " << bantu->tanggal << " | " << bantu->status << endl;
            ditemukan = true;
        }
        bantu = bantu->next;
    }
    if (!ditemukan) {
        cout << "Tidak ada habit yang sesuai.\n";
    }
}

void updateHabit(int idUpdate) {
    Habit* bantu = head;
    while (bantu) {
        if (bantu->id == idUpdate) {
            string namaBaru, tanggalBaru, statusBaru;
            cout << "Habit ditemukan. Masukkan data baru:\n";
            cout << "Nama baru: "; getline(cin, namaBaru);
            cout << "Tanggal baru: "; getline(cin, tanggalBaru);
            cout << "Status baru (sudah/belum): "; getline(cin, statusBaru);
            if (namaBaru.empty() || tanggalBaru.empty() || (statusBaru != "sudah" && statusBaru != "belum")) {
                cout << "Input tidak valid. Perubahan dibatalkan.\n";
                return;
            }
            bantu->nama = namaBaru;
            bantu->tanggal = tanggalBaru;
            bantu->status = statusBaru;
            cout << "Data habit berhasil diperbarui.\n";
            return;
        }
        bantu = bantu->next;
    }
    cout << "Habit tidak ditemukan.\n";
}

void hapusHabit(int idHapus) {
    if (!head) {
        cout << "Data habit masih kosong\n";
        return;
    }

    Habit* bantu = head;
    Habit* prev = nullptr;

    while (bantu) {
        if (bantu->id == idHapus) {
            if (!prev) {
                head = bantu->next;
            } else {
                prev->next = bantu->next;
            }
            cout << "Habit " << bantu->nama << " berhasil dihapus\n";
            delete bantu;
            return;
        }
        prev = bantu;
        bantu = bantu->next;
    }
    cout << "Habit tidak ditemukan.\n";
}

void urutkanNamaHabit() {
    if (!head || !head->next) return;

    Habit* current = head;
    Habit* index = nullptr;
    while (current) {
        index = current->next;
        while (index) {
            if (current->nama > index->nama) {
                swap(current->nama, index->nama);
                swap(current->tanggal, index->tanggal);
                swap(current->status, index->status);
                swap(current->id, index->id);
            }
            index = index->next;
        }
        current = current->next;
    }
}

void urutkanTanggalHabit() {
    if (!head || !head->next) return;

    Habit* current = head;
    Habit* index = nullptr;
    while (current) {
        index = current->next;
        while (index) {
            if (stoi(current->tanggal) > stoi(index->tanggal)) {
                swap(current->nama, index->nama);
                swap(current->tanggal, index->tanggal);
                swap(current->status, index->status);
                swap(current->id, index->id);
            }
            index = index->next;
        }
        current = current->next;
    }
}

void simpanHabit() {
    ofstream file("habits.txt");
    if (!file) {
        cout << "Gagal membuka file untuk menyimpan data.\n";
        return;
    }

    Habit* bantu = head;
    while (bantu) {
        file << bantu->id << "|" << bantu->nama << "|" << bantu->tanggal << "|" << bantu->status << "\n";
        bantu = bantu->next;
    }
    file.close();
    cout << "Data habit berhasil disimpan ke file.\n";
}

int main() {
    int pilihan;
    string nama, tanggal, status, kataCari;
    FILE* fileHabit;
    fileHabit = fopen("habits.txt", "r");
    if (fileHabit == NULL) {
        cout << "Gagal membuka file habits.txt. Membuat file baru.\n";
        fileHabit = fopen("habits.txt", "w");
        fclose(fileHabit);
    } else {
        fclose(fileHabit);
        cout << "File habits.txt ditemukan. Data akan dimuat dari file.\n";
        ifstream file("habits.txt");
        int idBaca;
        char pemisah;
        if (file.is_open()) {
            while (file >> idBaca >> pemisah && getline(file, nama, '|') && getline(file, tanggal, '|') && getline(file, status)) {
                Habit* baru = new Habit{nama, tanggal, status, idBaca, nullptr};
                if (!head) {
                    head = baru;
                } else {
                    Habit* temp = head;
                    while (temp->next) temp = temp->next;
                    temp->next = baru;
                }
                if (idBaca >= habitCounter) habitCounter = idBaca + 1;
            }
            file.close();
            cout << "Data habit berhasil dimuat dari file.\n";
        } else {
            cout << "Gagal membuka file untuk memuat data.\n";
        }
    }

    do {
        cout << "\n=======================\n";
        cout << " Aplikasi Habit Tracker\n";
        cout << "=======================\n";
        cout << "Menu:\n";
        cout << "1. Tambah Habit\n";
        cout << "2. Tampilkan Habit\n";
        cout << "3. Cari Habit\n";
        cout << "4. Update Habit\n";
        cout << "5. Urutkan Habit\n";
        cout << "6. Hapus Habit\n";
        cout << "7. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                cout << "Masukkan nama habit: "; getline(cin, nama);
                cout << "Masukkan tanggal habit (format angka): "; getline(cin, tanggal);
                cout << "Masukkan status habit (sudah/belum): "; getline(cin, status);
                tambahHabit(nama, tanggal, status);
                simpanHabit();
                break;
            case 2:
                tampilkanHabit();
                break;
            case 3:
                cout << "Masukkan habit yang dicari: "; getline(cin, kataCari);
                cariHabit(kataCari);
                break;
            case 4:
                int idUpdate;
                cout << "Masukkan ID habit yang akan diupdate: "; cin >> idUpdate; cin.ignore();
                updateHabit(idUpdate);
                simpanHabit();
                break;
            case 5:
                int pil;
                cout << "Urutkan habit berdasarkan:\n";
                cout << "1. Nama\n";
                cout << "2. Tanggal\n";
                cout << "Pilih opsi: ";
                cin >> pil; cin.ignore();
                if (pil == 1) {
                    urutkanNamaHabit();
                    cout << "Habit berhasil diurutkan berdasarkan nama.\n";
                } else if (pil == 2) {
                    urutkanTanggalHabit();
                    cout << "Habit berhasil diurutkan berdasarkan tanggal.\n";
                } else {
                    cout << "Pilihan tidak valid. Silakan coba lagi.\n";
                }
                break;
            case 6:
                int idHapus;
                cout << "Masukkan ID habit yang akan dihapus: "; cin >> idHapus; cin.ignore();
                hapusHabit(idHapus);
                simpanHabit();
                break;
            case 7:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (pilihan != 7);

    return 0;
}
