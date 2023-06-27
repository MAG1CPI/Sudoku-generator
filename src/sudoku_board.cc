#include "sudoku_board.h"
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

static const char kSeparation[] = "-----------------";

SudokuBoard::SudokuBoard() {
    boards.clear();
}

SudokuBoard::~SudokuBoard() {
}

int SudokuBoard::load(string path) {
    ifstream infile;
    infile.open(path);
    if (!infile.is_open()) {
        cout << "无法打开文件!" << endl;
        exit(-1);
    }

    boards.clear();

    char line[128];
    Board board;
    vector<char> row;
    while (!infile.eof()) {
        infile.getline(line, 128);
        if (line[0] == '-') {
            boards.push_back(board);
            board.clear();
        } else {
            row.clear();
            for (int i = 0; i < 128; i++) {
                if (line[i] != ' ') {
                    row.push_back(line[i]);
                }
            }
            board.push_back(row);
        }
    }

    infile.close();
    return 0;
}

int SudokuBoard::save(string path) {
    ofstream outfile;
    outfile.open(path);
    if (!outfile.is_open()) {
        cout << "无法打开文件!" << endl;
        exit(-1);
    }

    for (int k = 0; k < boards.size(); k++) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                outfile << boards[k][i][j] << " ";
            }
            outfile << endl;
        }
        outfile << kSeparation << "board[" << k + 1 << "]\n";
    }

    outfile.close();
    return 0;
}

void SudokuBoard::output() {
    for (int k = 0; k < boards.size(); k++) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cout << boards[k][i][j] << " ";
            }
            cout << endl;
        }
        cout << kSeparation << "board[" << k + 1 << "]\n";
    }
}

void SudokuBoard::print_board(Board& board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}