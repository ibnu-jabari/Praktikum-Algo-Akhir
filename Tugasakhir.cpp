#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Habit {
    string nama;
    string tanggal;
    string status;
    Habit* next;
};

Habit* head = nullptr;

void tambahHabit(string nama, string tanggal, string status) {
    Habit* baru = new Habit{nama, tanggal, status, nullptr};
    if (!head) {
        head = baru;
        cout<<"Node baru sukses jadi head"<<endl;
    } else {
        Habit* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = baru;
        cout<<"Node berhasil ditambahkan"<<endl;
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
        cout << "- " << bantu->nama << " | " << bantu->tanggal << " | " << bantu->status << endl;
        bantu = bantu->next;
    }
}


void cariHabit(string kataCari) {    
    Habit* bantu = head;
    bool ditemukan = false;

    while (bantu != nullptr) {
        if (bantu->nama.find(kataCari) != -1) {
            cout << "Ditemukan: " << bantu->nama << " | " << bantu->tanggal << " | " << bantu->status << endl;
            ditemukan = true;
        }
        bantu = bantu->next;
    }

    if (!ditemukan) {
        cout << "Tidak ada habit yang sesuai.\n";
    }
}

void updateHabit(string kataCari) {
    Habit* bantu = head;
    bool ditemukan = false;

    while (bantu) {
        if (bantu->nama.find(kataCari) != -1) {
            cout << "Habit ditemukan. Masukkan data baru:\n";
            cout << "Nama baru: "; getline(cin, bantu->nama);
            cout << "Tanggal baru: "; getline(cin, bantu->tanggal);
            cout << "Status baru: "; getline(cin, bantu->status);
            cout << "Data habit berhasil diperbarui.\n";
            ditemukan = true;
            break;
        }
        bantu = bantu->next;
    }

    if (!ditemukan) {
        cout << "Habit tidak ditemukan.\n";
    }
}
void urutkanNamaHabit() {
    if (!head || !head->next) return;  

    Habit* current = head;
    Habit* index = nullptr;
    string tempNama, tempTanggal, tempStatus;

    while (current) {
        index = current->next;
        while (index) {
            if (current->nama > index->nama) {
                
                tempNama = current->nama;
                tempTanggal = current->tanggal;
                tempStatus = current->status;

                current->nama = index->nama;
                current->tanggal = index->tanggal;
                current->status = index->status;

                index->nama = tempNama;
                index->tanggal = tempTanggal;
                index->status = tempStatus;
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
    string tempNama, tempTanggal, tempStatus;

    while (current) {
        index = current->next;
        while (index) {
            // mengubah string tanggal menjadi int untuk perbandingan
            if (stoi(current->tanggal) > stoi(index->tanggal)) {
                // Tukar data
                tempNama = current->nama;
                tempTanggal = current->tanggal;
                tempStatus = current->status;

                current->nama = index->nama;
                current->tanggal = index->tanggal;
                current->status = index->status;

                index->nama = tempNama;
                index->tanggal = tempTanggal;
                index->status = tempStatus;
            }
            index = index->next;
        }
        current = current->next;
    }
}
void hapusHabit(string kataHapus){
    if(head == nullptr){
        cout << "Data habit masih kosong\n";
        return;
    }

    Habit* bantu = head;
    Habit* prev = nullptr;
    bool ditemukan = false;

    while (bantu != nullptr) {
        if(bantu->nama.find(kataHapus)!= -1){
            if(prev == nullptr){
                head = bantu -> next;
            }else{
                prev -> next = bantu -> next;
            }   
            cout << "Habit " << bantu->nama << " berhasil dihapus\n";
            delete bantu;
            return;
        }
        prev = bantu;
        bantu = bantu -> next;
    }
    if(! ditemukan){
        cout << " Tidak ada habit yang sesuai\n";
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
        file << bantu->nama << "|" << bantu->tanggal << "|" << bantu->status << "\n";
        bantu = bantu->next;
    }
    file.close();
    cout << "Data habit berhasil disimpan ke file.\n";
}

int main() {
    int pilihan;
    string nama, tanggal, status, kataCari;
    FILE* habits;
    habits = fopen("habits.txt", "r");
    if (habits == NULL) {
        cout << "Gagal membuka file habits.txt. Membuat file baru.\n";
        habits = fopen("habits.txt", "w");
        fclose(habits);
    } else {
        fclose(habits);
        cout << "File habits.txt ditemukan. Data akan dimuat dari file.\n";
        ifstream file("habits.txt");
        if (file.is_open()) {
            while (getline(file, nama, '|') && getline(file, tanggal, '|') && getline(file, status)) {
                tambahHabit(nama, tanggal, status);
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
                cout << "Masukkan tanggal habit: "; getline(cin, tanggal);
                cout << "Masukkan status habit: "; getline(cin, status);
                tambahHabit(nama, tanggal, status);
                simpanHabit();
                break;
            case 2:
                tampilkanHabit();
                break;
            case 3:
                if (!head) {
                    cout << "Data habit masih kosong.\n";
                    break;
                }
                cout << "Masukkan habit yang dicari: "; getline(cin, kataCari);
                cariHabit(kataCari);
                break;
            case 4:
             if (!head) {
                    cout << "Data habit masih kosong.\n";
                    break;
                }
                cout << "Masukkan habit yang akan diupdate: "; getline(cin, kataCari);
                updateHabit(kataCari);
                simpanHabit(); 
                break;
            case 5:
                int pil;
                cout << "Urutkan habit berdasarkan:\n";
                cout << "1. Nama\n";
                cout << "2. Tanggal\n"; 
                cout << "Pilih opsi: ";
                cin >> pil;
                cin.ignore(); 
                if (pil == 1) {
                    urutkanNamaHabit();
                    if (!head) {
                        cout << "Data habit masih kosong!\n";
                        break;
                    }
                    if ( !head->next)  // Cek apakah hanya ada satu habit
                    {
                        cout << "Hanya ada satu habit, tidak perlu diurutkan.\n";
                        break;
                    }                    
                    cout << "Habit berhasil diurutkan berdasarkan nama.\n";
                    tampilkanHabit();

                } else if (pil == 2) {
                    urutkanTanggalHabit();
                     if (!head) {
                        cout << "Data habit masih kosong!\n";
                        break;
                    }
                    if ( !head->next)  // Cek apakah hanya ada satu habit
                    {
                        cout << "Hanya ada satu habit, tidak perlu diurutkan.\n";
                        break;
                    }          
                } else {
                    cout << "Pilihan tidak valid. Silakan coba lagi.\n";
                }
                 cout << "Habit berhasil diurutkan berdasarkan tanggal.\n";
                    tampilkanHabit();

                break;
            case 6:
                if (!head) {
                    cout << "Data habit masih kosong.\n";
                    break;
                }
                cout << "Masukkan nama habit yang akan dihapus: "; getline(cin, kataCari);
                hapusHabit(kataCari);
                simpanHabit(); 
                tampilkanHabit();
                break;
            case 7:
                cout << "Keluar dari program...\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (pilihan != 7);

    return 0;
}
