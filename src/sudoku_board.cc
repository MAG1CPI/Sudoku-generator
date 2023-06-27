// Copyright 2023 MAG1CPI
#include <cstring>
#include <fstream>
#include <iostream>
#include "../include/sudoku_board.h"

static const char kSeparation[] = "-----------------";

SudokuBoard::SudokuBoard() {
    boards.clear();
}

SudokuBoard::~SudokuBoard() {
}

int SudokuBoard::load(std::string path) {
    std::ifstream infile;
    infile.open(path);
    if (!infile.is_open()) {
        std::cout << "无法打开文件!\n";
        exit(-1);
    }

    boards.clear();

    char line[128];
    Board board;
    std::vector<char> row;
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

int SudokuBoard::save(std::string path) {
    std::ofstream outfile;
    outfile.open(path);
    if (!outfile.is_open()) {
        std::cout << "无法打开文件!\n";
        exit(-1);
    }

    for (int k = 0; k < boards.size(); k++) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                outfile << boards[k][i][j] << " ";
            }
            outfile << "\n";
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
                std::cout << boards[k][i][j] << " ";
            }
            std::cout << "\n";
        }
        std::cout << kSeparation << "board[" << k + 1 << "]\n";
    }
}

void SudokuBoard::print_board(const Board& board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << "\n";
    }
}
