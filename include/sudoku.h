#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#include <string>
#include "sudoku_board.h"

using namespace std;

class Sudoku {
   private:
    SudokuBoard game;

    struct State {
        int row[9];
        int col[9];
        int block[9];
        void flip(int i, int j, int num) {
            row[i] ^= (1 << num);
            col[j] ^= (1 << num);
            block[(i / 3) * 3 + j / 3] ^= (1 << num);
        }
    } state;
    vector<pair<int, int>> blanks;
    SudokuBoard result;

   public:
    Sudoku();
    ~Sudoku();

    int gen_endgames(int num);
    int gen_games(int num, int level, int min_hole, int max_hole, bool is_unique);
    int solve_games(string path);
    void save_board(string path);

   private:
    void gen_endgame(Board& board);
    void random_row_permutation(char* row);
    void row_col_extend(Board& board, int x, int y, int is_row);

    void solve_game(Board& board);
    void init_state(Board& board);
    void solve_by_dfs(Board& board, int i);
};

#endif