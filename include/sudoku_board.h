#ifndef _SUDOKU_BOARD_H_
#define _SUDOKU_BOARD_H_

#include <string>
#include <vector>
using namespace std;

// typedef char Board[9][9];
// typedef Board(*pBoard);
typedef vector<vector<char>> Board;

class Sudoku;

class SudokuBoard {
    friend class Sudoku;

   private:
    vector<Board> boards;

   public:
    SudokuBoard();
    ~SudokuBoard();

    int load(string path);
    int save(string path);
    int output();
};

#endif