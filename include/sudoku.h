#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#include <string>
#include "sudoku_board.h"

using namespace std;

class Sudoku {
   private:
    SudokuBoard games;
    SudokuBoard result;

    // 数独求解辅助数据结构
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

   public:
    Sudoku();
    ~Sudoku();

    int gen_endgames(int num);
    int gen_games(int num, int level, int min_hole_num, int max_hole_num, bool is_unique);
    int solve_games_and_save_results(string path);
    int save_games(string path);

   private:
    // 终局生成辅助函数
    void gen_endgame(Board& board);
    void random_row_permutation(char* row);
    void row_col_extend(Board& board, int x, int y, int is_row);

    // 数独求解辅助函数
    bool solve_game(Board& board, bool is_unique);
    void init_state(Board& board);
    bool solve_by_dfs(Board& board, int i, bool is_unique);

    // 数独生成辅助函数
    void set_hole_num_range(int level, int& min_hole_num, int& max_hole_num);
    bool dig_hole(Board& board, int hole, bool is_unique);
};

#endif