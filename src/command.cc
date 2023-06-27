#include "command.h"
#include <string.h>
#include <iostream>
#include "getopt.h"
#include "sudoku.h"

using namespace std;

Command::Command() {
    is_create = false;
    is_solve = false;
    is_generate = false;

    // 额外选项的初始化
    game_level = -1;
    min_hole_num = -1;
    max_hole_num = -1;
    is_unique = false;
}

Command::~Command() {
}

int Command::parse_arg(int argc, char* argv[]) {
    char opt = 0;
    int option_mru = 0;
    while ((opt = getopt(argc, argv, "c:s:n:m:r:u")) != -1) {
        switch (opt) {
            case 'c':
                is_create = true;
                endgame_num = atoi(optarg);
                if (endgame_num < 1 || endgame_num > 1000000) {
                    cout << "选项 -c 生成数独终盘数量的参数可选值为 1~1000000 ! 请输入一个合法值!\n";
                    exit(-1);
                }
                break;
            case 's':
                is_solve = true;
                game_path = optarg;
                // 文件是否可读的检查在solve里处理
                break;
            case 'n':
                is_generate = true;
                game_num = atoi(optarg);
                if (game_num < 1 || game_num > 10000) {
                    cout << "选项 -n 生成数独游戏数量的参数可选值为 1~10000 ! 请输入一个合法值!\n";
                    exit(-1);
                }
                break;
            case 'm':
                option_mru |= 0x01;
                game_level = atoi(optarg);
                if (game_level < 1 || game_level > 3) {
                    cout << "选项 -m 游戏难度的参数可选值为 1~3 ! 请输入一个合法值!\n";
                    exit(-1);
                }
                break;
            case 'r':
                option_mru |= 0x02;
                char* str;
                str = strtok(optarg, "~");
                if (str == NULL) {
                    cout << "选项 -m 挖空范围需要一个范围参数(eg: 20~55)!\n";
                    exit(-1);
                }
                min_hole_num = atoi(str);

                str = strtok(NULL, "~");
                if (str == NULL) {
                    cout << "选项 -m 挖空范围需要一个范围参数(eg: 20~55)!\n";
                    exit(-1);
                }
                max_hole_num = atoi(str);

                str = strtok(NULL, "~");
                if (str) {
                    cout << "选项 -m 挖空范围需要一个范围参数(eg: 20~55)!\n";
                    exit(-1);
                }

                if (min_hole_num > max_hole_num) {
                    cout << "请输入合法范围!\n";
                    exit(-1);
                } else if (min_hole_num < 20 || max_hole_num > 55) {
                    cout << "挖空数量可选范围为 20~55 ! 请输入一个合法参数值!\n";
                    exit(-1);
                }
                break;
            case 'u':
                option_mru |= 0x04;
                is_unique = true;
                break;
            default:
                cout << "选项错误！请输入合法选项!\n";
                exit(-1);
        }
    }
    if (is_generate == false && option_mru) {
        cout << "参数 -m , -r , -u 必须和参数 -n 一同使用!\n";
        exit(-1);
    }
    if (optind < argc) {
        cout << "参数错误！请输入合法参数!\n";
        exit(-1);
    }
    return 0;
}

void Command::handle() {
    if (is_create) {
        Sudoku sudoku;
        sudoku.gen_endgame(endgame_num);
        sudoku.save_board("./endgame.txt");
    }
    if (is_solve) {
        cout << "1\n";
        Sudoku sudoku;
        sudoku.solve(game_path);
        sudoku.save_board("./solve.txt");
    }
    if (is_generate) {
        Sudoku sudoku;
        sudoku.gen_game(game_num, game_level, min_hole_num, max_hole_num, is_unique);
        sudoku.save_board("./game.txt");
    }
}

void Command::output() {
    if (is_create) {
        cout << "创建" << endgame_num << "个终局\n\n";
    }
    if (is_solve) {
        cout << "求解路径为\"" << game_path << "\"的文件中的数独游戏\n\n";
    }
    if (is_generate) {
        cout << "创建" << game_num << "个数独游戏\n";
        if (game_level != -1) {
            cout << "游戏难度为: " << game_level << endl;
        }
        if (min_hole_num != -1) {
            cout << "挖空数量为: " << min_hole_num << " ~ " << max_hole_num << endl;
        }
        if (is_unique) {
            cout << "游戏的解唯一" << endl;
        }
    }
}