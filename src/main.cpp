#include "game.h"
#include "util.h"
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
    // Hosting
    case 1: {
        game.host_game();
    } break;
    // Joining
    case 2: {
        game.join_game();
    } break;
    }

    std::cout << "\nJoining Lobby...\n\n";

    game.play();

    return 0;
}