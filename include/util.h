#ifndef BATTLESHIP_UTIL_H
#define BATTLESHIP_UTIL_H

#include <iostream>
#include <sstream>
#include <streambuf>
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

struct NullBuf : std::streambuf {
    char buffer[100];
    int overflow(int c) override {
        setp(buffer, buffer + sizeof buffer);
        return c;
    }
    std::streamsize xsputn(const char *, std::streamsize n) override {
        return n;
    }
};
} // namespace util
} // namespace battleship

#endif