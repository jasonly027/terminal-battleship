#ifndef BATTLESHIP_GAME_H
#define BATTLESHIP_GAME_H

#include "client.h"
#include <cstdint>
#include <string>
#include "server.h"
#include <memory>

namespace battleship {
class Game {
public:
    static constexpr size_t kMaxPlayers = 2;

    void host_game();
    void join_game();
    void play();
private:
    bool start_server(uint16_t port = 49494);
    void stop_server();

    bool start_client(const std::string &host, uint16_t port = 49494);
    void stop_client();


    std::unique_ptr<Server> p_server_;
    std::unique_ptr<Client> p_client_;
};
} // namespace battleship

#endif