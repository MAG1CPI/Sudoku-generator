#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <string>
using namespace std;

class Command {
   private:
    // 数独终局
    bool is_create;
    int endgame_num;

    // 数独求解
    bool is_solve;
    string game_path;

    // 数独游戏
    int is_generate;
    int game_num;
    int game_level;
    int min_hole_num;
    int max_hole_num;
    bool is_unique;

   public:
    // 分析参数
    int parse_arg(int argc, char* argv[]);
    // 处理
    void handle();
    // 显示
    void output();
};

#endif