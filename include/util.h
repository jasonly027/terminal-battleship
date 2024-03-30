#ifndef BATTLESHIP_UTIL_H
#define BATTLESHIP_UTIL_H
#include <cstdint>
#pragma once

#include <iostream>
#include <sstream>
#include <string>

namespace battleship {
namespace util {
template <typename T> T get_input() {
    T ret;
    bool is_not_valid_input = true;
    do {
        // Get raw input
        std::string in;
        std::getline(std::cin, in);

        // If input isn't an expected value,
        // reprompt for input
        std::istringstream iss(in);
        iss >> ret;
        if (iss && iss.eof()) {
            is_not_valid_input = false;
        } else {
            std::cout << "Invalid input\n"
                         "> ";
        }
    } while (is_not_valid_input);

    return ret;
}

int get_lobby_mode();
} // namespace util
} // namespace battleship

#endif