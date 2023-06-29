// Copyright 2023 MAG1CPI
#ifndef INCLUDE_SUDOKU_BOARD_H_
#define INCLUDE_SUDOKU_BOARD_H_

#include <string>
#include <vector>

typedef std::vector<std::vector<char>> Board;

class Sudoku;

class SudokuBoard {
    friend class Sudoku;

 private:
    std::vector<Board> boards;

 public:
    SudokuBoard();
    ~SudokuBoard();

    int load(std::string path);
    int save(std::string path);
    void output();
};

#endif  // INCLUDE_SUDOKU_BOARD_H_
