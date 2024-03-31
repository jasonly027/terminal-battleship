#include "client.h"
#include "game.h"
#include "message_factory.h"
#include "message_types.h"
#include <cstddef>
#include <iostream>

using namespace battleship;

Client::Client(std::ostream &log) : client_interface(log) {}

void Client::ping() { send(Msg::Ping()); }

void Client::listen() {
    while (connected()) {
        incoming().wait();

        while (!incoming().empty()) {
            auto msg = incoming().pop_front().msg;

            switch (msg.kind()) {
            case MessageType::LobbyStatus: {
                size_t players;
                msg >> players;
                std::cout << "[" << players << " / " << Game::kMaxPlayers << "] Players in the Lobby\n";
            } break;
            case MessageType::StartingGame: {
                std::cout << "\nGame is starting!\n";
            }
            }
        }
    }
}