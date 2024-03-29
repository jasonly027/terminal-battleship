#ifndef BATTLESHIP_GAME_H
#define BATTLESHIP_GAME_H
#pragma once

#include "server.h"
#include <memory>

namespace battleship {
class Game {
public:
    void start_server();

private:
    std::unique_ptr<Server> p_server_;
    std::thread server_thread_;
};
} // namespace battleship

#endif