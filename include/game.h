#ifndef BATTLESHIP_GAME_H
#define BATTLESHIP_GAME_H
#include <cstdint>
#pragma once

#include "server.h"
#include <memory>

namespace battleship {
class Game {
public:
    ~Game();

    bool start_server(uint16_t port = 49494);
    void stop_server();

    void start_host_client();
    void stop_host_client();

    void start_join_client();
    void stop_join_client();

private:
    std::unique_ptr<Server> p_server_;
};
} // namespace battleship

#endif