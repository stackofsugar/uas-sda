#pragma once
#include <iostream>
#include <limits>
using namespace std;

template<typename Ty>
Ty input(Ty floor = 0, Ty ceil = numeric_limits<Ty>::max()) {
    Ty buffer;
    while (1) {
        if (cin >> buffer) {
            if (buffer < floor) {
                cout << "Masukan anda terlalu kecil! Coba lagi:  ";
            }
            else if (buffer > ceil) {
                cout << "Masukan anda terlalu besar! Coba lagi: ";
            }
            else {
                return buffer;
            }
        }
        else {
            cout << "Masukan anda tidak valid! Coba lagi: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}