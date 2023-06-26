#include "soduku_borad.h"
#include <iostream>

using namespace std;

int SodukuBorad::load(string path) {
    // TODO
    return 0;
}
int SodukuBorad::save(string path) {
    // TODO
    return 0;
}
int SodukuBorad::output() {
    for (int k = 0; k < boards.size(); k++) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cout << boards[k][i][j] << " ";
            }
            cout << endl;
        }
        cout << "-----------------\n";
    }
    cout << endl;
    return 0;
}