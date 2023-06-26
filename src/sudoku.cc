#include <iostream>
#include "command.h"

using namespace std;

int main(int argc, char* argv[]) {
    Command command;
    command.parse_arg(argc, argv);
    command.output();
    command.handle();
    return 0;
}