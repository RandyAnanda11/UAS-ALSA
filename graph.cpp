#include <iostream>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct simpul {
    string info;
    simpul* left, * right;
};

simpul* p, * first, * last, * Q, * R;
simpul* points[4];
int A[4][4] = {
        {0, 6, 5, 9},
        {6, 0, 2, 8},
        {5, 2, 0, 7},
        {9, 8, 7, 0},
    };

    string namaKota[] = {"K", "L", "M", "N"};
    int i, j;
    int banyakKota = sizeof(namaKota) / sizeof(namaKota[0]);

void TampilkanJarakAntarKota () {
    i = 0;
    j = 0;
    p = new simpul;
    p->info = namaKota[0];
    first = p;
    last = p;
    p->left = NULL;
    p->right = NULL;
    points[0] = p;

    for (i = 1; i < banyakKota; i++) {
        p = new simpul;
        p->info = namaKota[i];
        last->left = p;
        last = last->left;
        p->left = NULL;
        p->right = NULL;
        points[i] = p;
    }

    Q = first;
    for (i = 0; i < banyakKota; i++) {
        R = Q;
        cout << "-------------------------------------" << endl;
        cout << "x> Jarak Kota " << Q->info << endl;
        for (j = 0; j < banyakKota; j++) {
            if (A[i][j] != 0) {
                p = new simpul;
                p->info = namaKota[j];
                R->right = p;
                p->left = points[j];
                cout << "Ke Kota " << p->left->info << endl;
                cout << "Adalah: " << A[i][j] << " km" << endl;
                p->right = NULL;
                R = p;
            }
        }
        cout << endl;
        Q = Q->left;
    }

}

void HitungJarakTerpendek () {
    // Mencari jalur terpendek untuk memutari seluruh kota
    string vertexMulai;
    int urutanTerpilih[4];
    cout << "---------------------------------------------------------"<<endl;
    cout << "Masukkan Kota dimana anda akan memulai ekspedisi anda: ";
    cin >> vertexMulai;

    int urutanKunjungan[4];
    int indexAwal;

    // Mencari indeks dari vertex mulai
    for (i = 0; i < banyakKota; i++) {
        if (namaKota[i] == vertexMulai) {
            indexAwal = i;
            break;
        }
    }

    // Menginisialisasi urutan kunjungan
    for (i = 0; i < banyakKota; i++) {
        urutanKunjungan[i] = (indexAwal + i) % (banyakKota);
    }

    int jarakTerpendek = INF; // Men-set jarak terpendek dengan nilai yang sangat besar

    // Mencari semua permutasi yang dimulai dari indeks awal
    do {
        int Jarak = 0;

        for (i = 0; i < banyakKota - 1; i++) {
            int from = urutanKunjungan[i];
            int to = urutanKunjungan[i + 1];
            Jarak += A[from][to];
        }

        // Memperbarui jarak terpendek jika ditemukan jarak yang lebih kecil
        if (Jarak < jarakTerpendek) {
            for (int i = 0; i < banyakKota; i++) {
                urutanTerpilih[i] = urutanKunjungan[i];
            }
            jarakTerpendek = Jarak;
        }
    } while (next_permutation(urutanKunjungan + 1, urutanKunjungan + banyakKota));

    // Menampilkan jarak terpendek yang dapat dicapai
    cout << "Jarak terpendek yang dapat dicapai: " << jarakTerpendek << " Km" << endl;
    cout << "Dengan urutan kunjungan sebagai berikut: ";
    for (int i = 0; i < banyakKota; i++) {
        cout << namaKota[urutanTerpilih[i]] << " ";
    }
    cout << endl;
}

void TampilkanMenu () {
    cout << endl;
    cout << "-----------------------------------------------------------"<<endl;
    cout << "1. Tampilkan jarak antar kota" << endl;
    cout << "2. Cari jarak terpendek" << endl;
    cout << "3. EXIT"<<endl;
    cout << "------------------------------------------------------------" << endl;


}
int main() {

    cout << "Selamat datang, Sales Randy. Untuk memulai ekspedisi Anda, silakan pilih menu (masukkan angka):" << endl;
    int pilihan;
    do{
        TampilkanMenu();
        cin >> pilihan;
        switch (pilihan) {
            case 1:
                TampilkanJarakAntarKota();
                break;
            case 2:
                HitungJarakTerpendek();
                break;
            case 3:
                cout << "Exiting The Program..." << endl;
                break;
            }
    } while (pilihan != 3);
    
    return 0;
}
