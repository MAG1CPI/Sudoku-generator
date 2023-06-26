#ifndef _SODOKU_BORAD_H_
#define _SODOKU_BORAD_H_

#include <string>
#include <vector>
using namespace std;

class SodukuBorad {
    typedef char Board[9][9];

   private:
    vector<Board> boards;

   public:
    int load(string path);
    int save(string path);
    int output();
};

#endif