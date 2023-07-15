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

int main() {
    int A[4][4] = {
        {0, 6, 9, 5},
        {6, 0, 2, 8},
        {5, 2, 0, 7},
        {9, 8, 7, 0},
    };

    string AbjadSimpul[] = {"K", "L", "M", "N"};
    int i, j;
    int urutanTerpilih[4];

    i = 0;
    j = 0;
    p = new simpul;

    p->info = AbjadSimpul[0];
    first = p;
    last = p;
    p->left = NULL;
    p->right = NULL;
    points[0] = p;

    for (i = 1; i < sizeof(AbjadSimpul) / sizeof(AbjadSimpul[0]); i++) {
        p = new simpul;
        p->info = AbjadSimpul[i];
        last->left = p;
        last = last->left;
        p->left = NULL;
        p->right = NULL;
        points[i] = p;
    }

    Q = first;
    for (i = 0; i < sizeof(AbjadSimpul) / sizeof(AbjadSimpul[0]); i++) {
        R = Q;
        cout << "vertex " << Q->info << endl;
        for (j = 0; j < sizeof(AbjadSimpul) / sizeof(AbjadSimpul[0]); j++) {
            if (A[i][j] != 0) {
                p = new simpul;
                p->info = AbjadSimpul[j];
                R->right = p;
                p->left = points[j];
                cout << "berhubungan dengan: " << p->left->info << endl;
                cout << "bobot: " << A[i][j] << endl;
                p->right = NULL;
                R = p;
            }
        }
        cout << endl;
        Q = Q->left;
    }

    // Mencari jalur terpendek untuk memutari seluruh kota
    string vertexMulai;
    cout << "Masukkan vertex mulai: ";
    cin >> vertexMulai;

    int urutanKunjungan[4];
    int indexAwal;

    // Mencari indeks dari vertex mulai
    for (i = 0; i < sizeof(AbjadSimpul) / sizeof(AbjadSimpul[0]); i++) {
        if (AbjadSimpul[i] == vertexMulai) {
            indexAwal = i;
            break;
        }
    }

    // Menginisialisasi urutan kunjungan
    for (i = 0; i < sizeof(AbjadSimpul) / sizeof(AbjadSimpul[0]); i++) {
        urutanKunjungan[i] = (indexAwal + i) % (sizeof(AbjadSimpul) / sizeof(AbjadSimpul[0]));
    }

    int jarakTerpendek = INF; // Men-set jarak terpendek dengan nilai yang sangat besar

    // Mencari semua permutasi yang dimulai dari indeks awal
    do {
        int Jarak = 0;

        for (i = 0; i < sizeof(AbjadSimpul) / sizeof(AbjadSimpul[0]) - 1; i++) {
            int from = urutanKunjungan[i];
            int to = urutanKunjungan[i + 1];
            Jarak += A[from][to];
        }

        // Memperbarui jarak terpendek jika ditemukan jarak yang lebih kecil
        if (Jarak < jarakTerpendek) {
            for (int i = 0; i < sizeof(AbjadSimpul) / sizeof(AbjadSimpul[0]); i++) {
                urutanTerpilih[i] = urutanKunjungan[i];
            }
            jarakTerpendek = Jarak;
        }
    } while (next_permutation(urutanKunjungan + 1, urutanKunjungan + sizeof(AbjadSimpul) / sizeof(AbjadSimpul[0])));

    // Menampilkan jarak terpendek yang dapat dicapai
    cout << "Jarak terpendek yang dapat dicapai: " << jarakTerpendek << endl;
    cout << "Dengan urutan kunjungan sebagai berikut: ";
    for (int i = 0; i < sizeof(AbjadSimpul) / sizeof(AbjadSimpul[0]); i++) {
        cout << AbjadSimpul[urutanTerpilih[i]] << " ";
    }
    cout << endl;

    return 0;
}
