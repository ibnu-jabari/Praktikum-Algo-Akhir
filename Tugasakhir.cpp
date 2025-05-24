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


