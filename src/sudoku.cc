#include "sudoku.h"
#include <assert.h>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

Sudoku::Sudoku() {
}

Sudoku::~Sudoku() {
}

int Sudoku::gen_endgames(int num) {
    for (int i = 0; i < num; i++) {
        Board board(9, vector<char>(9, '$'));
        gen_endgame(board);
        games.boards.push_back(board);
    }
    games.output();
    return 0;
}

int Sudoku::gen_games(int num, int level, int min_hole_num, int max_hole_num, bool is_unique) {
    set_hole_num_range(level, min_hole_num, max_hole_num);
    while (num > 0) {
        Board board(9, vector<char>(9, '$'));
        gen_endgame(board);

        // 挖洞
        int hole = min_hole_num + rand() % (max_hole_num - min_hole_num + 1);
        if (dig_hole(board, hole, is_unique) == false) {
            continue;
        }

        games.boards.push_back(board);
        num--;
    }
    games.output();
    return 0;
}

int Sudoku::solve_games_and_save_results(string path) {
    games.load(path);
    games.output();
    int i = 1;
    for (Board board : games.boards) {
        solve_game(board, false);

        string file_name = "board" + to_string(i) + "'s results.txt";
        result.save(file_name);

        cout << "----result of board[" << i << "]----\n";
        result.output();
        i++;
    }
    // games.output();
    return 0;
}

int Sudoku::save_games(string path) {
    return games.save(path);
}

void Sudoku::gen_endgame(Board& board) {
    char row[9];
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
    int order1[3] = {1, 2, 0};
    int order2[3] = {2, 0, 1};
    if (rand() % 2) {
        swap(order1, order2);
    }
    for (int i = 0; i < 3; i++) {
        if (is_row) {
            board[x][i] = board[x + order1[0]][y + i];
            board[x + 1][i] = board[x + order1[1]][y + i];
            board[x + 2][i] = board[x + order1[2]][y + i];
            board[x][i + 6] = board[x + order2[0]][y + i];
            board[x + 1][i + 6] = board[x + order2[1]][y + i];
            board[x + 2][i + 6] = board[x + order2[2]][y + i];
        } else {
            board[i][y] = board[x + i][y + order1[0]];
            board[i][y + 1] = board[x + i][y + order1[1]];
            board[i][y + 2] = board[x + i][y + order1[2]];
            board[i + 6][y] = board[x + i][y + order2[0]];
            board[i + 6][y + 1] = board[x + i][y + order2[1]];
            board[i + 6][y + 2] = board[x + i][y + order2[2]];
        }
    }
}

bool Sudoku::solve_game(Board& board, bool is_unique) {
    init_state(board);
    return solve_by_dfs(board, 0, is_unique);
}

void Sudoku::init_state(Board& board) {
    memset(&state, 0, sizeof(state));
    blanks.clear();
    result.boards.clear();

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == '$') {
                blanks.push_back(pair<int, int>(i, j));
            } else {
                int n = board[i][j] - '1';
                state.flip(i, j, n);
            }
        }
    }
}

bool Sudoku::solve_by_dfs(Board& board, int i, bool is_unique) {
    if (i == blanks.size()) {
        result.boards.push_back(board);
        if (is_unique && result.boards.size() > 1) {
            return false;
        } else {
            return true;
        }
    }

    int x = blanks[i].first, y = blanks[i].second;

    int mask = state.row[x] | state.col[y] | state.block[(x / 3) * 3 + y / 3];

    for (int num = 0; num < 9; num++) {
        if ((mask & (1 << num)) == 0) {
            state.flip(x, y, num);
            board[x][y] = num + '1';
            if (solve_by_dfs(board, i + 1, is_unique) == false) {
                state.flip(x, y, num);
                board[x][y] = '$';
                return false;
            }
            state.flip(x, y, num);
        }
    }
    board[x][y] = '$';
    return true;
}

void Sudoku::set_hole_num_range(int level, int& min_hole_num, int& max_hole_num) {
    if (level != -1) {  // 存在 -m 选项则以 -m 选项为主
        switch (level) {
            case 1:
                min_hole_num = 20;
                max_hole_num = 30;
                break;
            case 2:
                min_hole_num = 30;
                max_hole_num = 40;
                break;
            case 3:
                min_hole_num = 40;
                max_hole_num = 55;
                break;
            default:
                min_hole_num = 20;
                max_hole_num = 55;
                break;
        }
    } else if (min_hole_num == -1) {  // 既没有 -m 选项也没有 -r 选项则完全随机挖洞
        min_hole_num = 20;
        max_hole_num = 55;
    }
}

bool Sudoku::dig_hole(Board& board, int hole_num, bool is_unique) {
    int count = 0;  // 记录错误次数，过高则重新生成基础图
    while (hole_num > 0) {
        int x = rand() % 9;
        int y = rand() % 9;
        if (board[x][y] == '$')
            continue;
        char temp = board[x][y];
        board[x][y] = '$';
        if (is_unique) {
            if (solve_game(board, is_unique) == true && result.boards.size() == 1) {
                hole_num--;
                count = 0;
            } else {
                board[x][y] = temp;
                if (count++ > 20) {
                    return false;
                }
            }
        } else {
            hole_num--;
        }
    }
    return true;
}