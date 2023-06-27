#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#include <string>
#include "sudoku_board.h"

using namespace std;

class Sudoku {
   private:
    SudokuBoard game;

   public:
    Sudoku();
    ~Sudoku();

    int gen_endgame(int num);
    int gen_game(int num, int level, int min_hole, int max_hole, bool is_unique);
    int solve(string path);
    void save_board(string path);

   private:
    void random_row_permutation(char* row);
    void row_col_extend(Board& board, int x, int y, int is_row);
};

#endif