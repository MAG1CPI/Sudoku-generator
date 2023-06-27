#include "sudoku.h"
#include <algorithm>
#include <iostream>
using namespace std;

Sudoku::Sudoku() {
}

Sudoku::~Sudoku() {
}

int Sudoku::gen_endgame(int num) {
    Board board(9, vector<char>(9, '$'));
    char row[9];

    for (int i = 0; i < num; i++) {
        random_row_permutation(row);
        for (int i = 0; i < 3; i++) {
            board[3][i + 3] = row[i] + '1';
            board[4][i + 3] = row[i + 3] + '1';
            board[5][i + 3] = row[i + 6] + '1';
        }
        row_col_extend(board, 3, 3, true);
        row_col_extend(board, 3, 3, false);
        row_col_extend(board, 3, 0, false);
        row_col_extend(board, 3, 6, false);
        game.boards.push_back(board);
    }
    game.output();
    return 0;
}

int Sudoku::gen_game(int num, int level, int min_hole, int max_hole, bool is_unique) {
    // TODO
    return 0;
}

int Sudoku::solve(string path) {
    // TODO
    return 0;
}

void Sudoku::save_board(string path) {
    game.save(path);
}

void Sudoku::random_row_permutation(char* row) {
    int i = 0;
    int mask = 0;
    while (i < 9) {
        int num = rand() % 9;
        if ((1 << num) & mask) {
            continue;
        } else {
            row[i++] = num;
            mask |= (1 << num);
        }
    }
}

void Sudoku::row_col_extend(Board& board, int x, int y, int is_row) {
    int order_first[3] = {1, 2, 0};
    int order_second[3] = {2, 0, 1};
    if (rand() % 2) {
        swap(order_first, order_second);
    }
    for (int i = 0; i < 3; i++) {
        if (is_row) {
            board[x][i] = board[x + order_first[0]][y + i];
            board[x + 1][i] = board[x + order_first[1]][y + i];
            board[x + 2][i] = board[x + order_first[2]][y + i];
            board[x][i + 6] = board[x + order_second[0]][y + i];
            board[x + 1][i + 6] = board[x + order_second[1]][y + i];
            board[x + 2][i + 6] = board[x + order_second[2]][y + i];
        } else {
            board[i][y] = board[x + i][y + order_first[0]];
            board[i][y + 1] = board[x + i][y + order_first[1]];
            board[i][y + 2] = board[x + i][y + order_first[2]];
            board[i + 6][y] = board[x + i][y + order_second[0]];
            board[i + 6][y + 1] = board[x + i][y + order_second[1]];
            board[i + 6][y + 2] = board[x + i][y + order_second[2]];
        }
    }
}