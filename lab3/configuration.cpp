//#include "configuration.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>


void Config::read_config(char *input_file) {
    std::string input_string = (std::string) input_file;
    if (input_string.substr(input_string.find('.')) != ".txt") {
        throw "format_error";
    }

    std::ifstream config(input_file);
    if (!config.is_open()) {
        throw "open_error";
    }

    std::string line;
    operation oper;
    while (std::getline(config, line)) {
        if (line[0] == '#') continue;

        if (line[1] == 'u') {
            oper.operation_type = '1';
            oper.start = 0;
            oper.finish = 0;
            oper.input_number = 1;
            std::istringstream temp(line);
            temp >> line >> oper.start >> oper.finish;
        }

        else if (line[1] == 'i') {
            oper.operation_type = '2';
            std::istringstream temp(line);
            oper.start = 0;
            oper.finish = 0;
            temp >> line >> line[0] >> oper.input_number >> oper.start >> oper.finish;
        }

        else if (line[0] == 'r') {
            oper.operation_type = '3';
            oper.start = 0;
            oper.finish = 0;
            oper.input_number = 1;
            std::istringstream temp(line);
            temp >> line >> oper.start >> oper.finish;
        }

        if (oper.finish < 0 || oper.start < 0)
            throw "negative_time";
        if (oper.finish < oper.start)
            throw "lt_finish_start";
        if (oper.finish != 0 && oper.finish == oper.start)
            throw "equality";
        operations.push_back(oper);
    }
    config.close();
}

operation Config::what_to_do(int id) {
    return operations[id];
}

int Config::how_much_work() {
    return (int) operations.size();
}
