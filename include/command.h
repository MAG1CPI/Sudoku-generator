// Copyright 2023 MAG1CPI
#ifndef INCLUDE_COMMAND_H_
#define INCLUDE_COMMAND_H_

#include <string>

class Command {
 private:
    // 数独终局
    bool is_create;
    int endgame_num;

    // 数独求解
    bool is_solve;
    std::string game_path;

    // 数独游戏
    int is_generate;
    int game_num;
    int game_level;
    int min_hole_num;
    int max_hole_num;
    bool is_unique;

 public:
    Command();
    ~Command();
    // 分析参数
    int parse_arg(int argc, char* argv[]);
    // 处理
    void handle();
    // 显示
    void output();
};

#endif  // INCLUDE_COMMAND_H_
