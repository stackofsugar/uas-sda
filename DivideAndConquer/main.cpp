#include "include/pch.h"
using namespace std;

int main() {
    bool running = true;
    string shell_input, errmsg;
    vector<int> data_vec;
    int min_max[2], *min_max_c, sum_vec;

    cout << ">> HitungArray <<\n(C) 2021 Christopher Digno\n"
        << "Guide dan Informasi: github.com/stackofsugar/uas-sda/tree/main/hitungarray\n"
        << "Petunjuk:\n -> Masukkan inputan array anda pada shell di bawah ini sesuai dengan guide\n"
        << " -> Masukkan 0 untuk keluar dari program\n"
        << " -> Hanya gunakan tipe data integer\n\n";

    while (running) {
        try {
            data_vec.clear();

            cout << "$ ";
            getline(cin, shell_input);
            if (shell_input[0] == '0') {
                return 0;
            }
            else {
                if (stringParser(shell_input, data_vec)) {
                    if (!data_vec.empty()) {
                        srand((unsigned)(time(NULL)));
                        min_max_c = min_max;

                        findMinMax(data_vec, &min_max_c);
                        sum_vec = sumElems(data_vec);

                        cout << "Rerata vektor = " << float(sum_vec / (float)data_vec.size())
                            << "\nJumlah elemen vektor = " << sum_vec
                            << "\nNilai minimum = " << min_max_c[0] << " dan maksimum = " << min_max_c[1]
                            << '\n';

                        quickSort(data_vec);

                        cout << "Vektor yang sudah diurutkan =\n[ ";
                        for_each(data_vec.begin(), data_vec.end(), [](const int &elem) {
                            cout << elem << ' ';
                            });
                        cout << "]\n\n";
                    }
                    else {
                        cout << "Masukan tidak valid! Masukan tidak boleh kosong.\n";
                    }
                }
                else {
                    cout << "Masukan tidak valid! Periksa kembali format.\n";
                }
            }
        }
        catch (exception &e) {
            errmsg = e.what();

            cout << "Masukan tidak valid! ";
            if (errmsg == "stoi") {
                cout << "Karakter yang diperbolehkan: '[', ']', ',', dan angka";
            }
            else {
                cout << errmsg;
            }
            cout << '\n';
        }
        catch (...) {
            cout << "Sebuah error yang tidak diketahui telah ditangkap.\n";
        }
    }
}