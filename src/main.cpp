#include "client.h"
#include "game.h"
#include "impl/message.h"
#include "message_types.h"
#include "util.h"
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

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
        game.start_server();
    }
    case 2: {
    }
    }

    Client c;
    c.connect("localhost", 49494);
    std::this_thread::sleep_for(std::chrono::seconds(4));
    while (1) {
        c.ping();
        std::this_thread::sleep_for(std::chrono::seconds(2));


        if (c.connected()) {
            std::cout << " I am connected\n";
            if (!c.incoming().empty()) {

                auto msg = c.incoming().pop_front().msg;

                switch (msg.header.id) {
                case MessageType::Ping: {
                    std::cout << "Server pong\n";
                } break;
                }
            }
        }
    }

    return 0;
}