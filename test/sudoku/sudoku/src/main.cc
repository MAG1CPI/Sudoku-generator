// Copyright 2023 MAG1CPI
#include <iostream>
#include "../include/command.h"

int main(int argc, char* argv[]) {
    Command command;
    if (command.parse_arg(argc, argv) == -1) {
        return -1;
    }
    command.output();
    command.handle();
    return 0;
}
