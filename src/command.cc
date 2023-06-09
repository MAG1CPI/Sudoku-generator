// Copyright 2023 MAG1CPI
#include <string.h>
#include <algorithm>
#include <iostream>
#include "../include/command.h"
#include "../include/getopt.h"
#include "../include/sudoku.h"

bool is_number(const std::string& s) {
    return std::all_of(s.begin(), s.end(), [](char c) { return isdigit(c) != 0; });
}

Command::Command() {
    is_create = false;
    is_solve = false;
    is_generate = false;

    endgame_num = 0;
    game_num = 0;
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
    int mask_mru = 0;  // |u|r|m|
    char *pTmp = NULL;
    while ((opt = getopt(argc, argv, "c:s:n:m:r:u")) != -1) {
        switch (opt) {
            case 'c':
                is_create = true;
                endgame_num = atoi(optarg);
                if (is_number(optarg) == false || endgame_num < 1 || endgame_num > 1000000) {
                    std::cout << "选项 -c 生成数独终盘数量的参数可选值为 1~1000000 ! 请输入一个合法值!\n";
                    return -1;
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
                if (is_number(optarg) == false || game_num < 1 || game_num > 10000) {
                    std::cout << "选项 -n 生成数独游戏数量的参数可选值为 1~10000 ! 请输入一个合法值!\n";
                    return -1;
                }
                break;
            case 'm':
                mask_mru |= 0x01;
                game_level = atoi(optarg);
                if (is_number(optarg) == false || game_level < 1 || game_level > 3) {
                    std::cout << "选项 -m 游戏难度的参数可选值为 1~3 ! 请输入一个合法值!\n";
                    return -1;
                }
                break;
            case 'r':
                mask_mru |= 0x02;
                char* str;
                str = strtok_s(optarg, "~", &pTmp);
                if (str == NULL || is_number(str) == false) {
                    std::cout << "选项 -r 挖空范围需要一个范围参数(eg: 20~55)!\n";
                    return -1;
                }
                min_hole_num = atoi(str);

                str = strtok_s(NULL, "~", &pTmp);
                if (str == NULL || is_number(str) == false) {
                    std::cout << "选项 -r 挖空范围需要一个范围参数(eg: 20~55)!\n";
                    return -1;
                }
                max_hole_num = atoi(str);

                str = strtok_s(NULL, "~", &pTmp);
                if (str) {
                    std::cout << "选项 -r 挖空范围需要一个范围参数(eg: 20~55)!\n";
                    return -1;
                }

                if (min_hole_num > max_hole_num) {
                    std::cout << "请输入合法范围!\n";
                    return -1;
                } else if (min_hole_num < 20 || max_hole_num > 55) {
                    std::cout << "挖空数量可选范围为 20~55 ! 请输入一个合法参数值!\n";
                    return -1;
                }
                break;
            case 'u':
                mask_mru |= 0x04;
                is_unique = true;
                break;
            default:
                std::cout << "选项错误！请输入合法选项!\n";
                return -1;
        }
    }
    if (optind < argc) {
        std::cout << "参数错误！请输入合法参数!\n";
        return -1;
    }

    if (is_generate == false && mask_mru) {
        std::cout << "选项 -m , -r , -u 必须和选项 -n 一同使用!\n";
        return -1;
    } else if (mask_mru & (mask_mru >> 1)) {
        std::cout << "选项 -m 和选项 -r 同时出现，以 -m 为主!\n";
    }

    return 0;
}

void Command::handle() {
    if (is_create) {
        std::cout << "\n--------生成终局--------\n";
        Sudoku sudoku;
        sudoku.gen_endgames(endgame_num);
        sudoku.save_games("./endgame.txt");
    }
    if (is_solve) {
        std::cout << "\n--------求解数独--------\n";
        Sudoku sudoku;
        sudoku.solve_games_and_save_results(game_path);
    }
    if (is_generate) {
        std::cout << "\n--------生成数独--------\n";
        Sudoku sudoku;
        sudoku.gen_games(game_num, game_level, min_hole_num, max_hole_num, is_unique);
        sudoku.save_games("./game.txt");
    }
}

void Command::output() {
    std::cout << "----------设置----------\n";
    if (is_create) {
        std::cout << "创建" << endgame_num << "个终局\n\n";
    }
    if (is_solve) {
        std::cout << "求解路径为\"" << game_path << "\"的文件中的数独游戏\n\n";
    }
    if (is_generate) {
        std::cout << "创建" << game_num << "个数独游戏\n";
        if (game_level != -1) {
            std::cout << "游戏难度为: " << game_level << std::endl;
        }
        if (min_hole_num != -1) {
            std::cout << "挖空数量为: " << min_hole_num << " ~ " << max_hole_num << std::endl;
        }
        if (is_unique) {
            std::cout << "游戏的解唯一" << std::endl;
        }
        std::cout << std::endl;
    }
}
