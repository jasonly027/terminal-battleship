#include "game.h"
#include "util.h"
#include <cstdint>
#include <cstdlib>
#include <iostream>

using namespace battleship;

int main() {
    Game game;

    std::cout << "Let's Play Battleship!\n\n"
                 "1 - Host Server\n"
                 "2 - Join Server\n"
                 "> ";
    int lobby_mode = util::get_lobby_mode();

    switch (lobby_mode) {
    case 1: {
        std::cout << "Enter Port\n"
                    "> ";
        const uint16_t port = util::get_input<uint16_t>();

        if (!game.start_server(port)) {
            std::cout << "Error starting server...\n";
            std::exit(0);
        }

        // game.start_host_client();
    }
    case 2: {
    }
    }

    return 0;
}