#include "util.h"

using namespace battleship;

int util::get_lobby_mode() {
    while (1) {
        int in = get_input<int>();
        switch (in) {
        case 1:
        case 2:
            return in;
        }
        std::cout << "Invalid input\n"
                     "> ";
    }
}