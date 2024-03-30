#include "game.h"
#include "server.h"
#include <cstdint>
#include <memory>

using namespace battleship;

Game::~Game() {
    stop_server();
}

bool Game::start_server(uint16_t port) {
    std::ostream null(nullptr);
    p_server_ = std::make_unique<Server>(port);
    if (p_server_->run()) {
        return true;
    }

    p_server_.reset();
    return false;
}

void Game::stop_server() {
    if (p_server_->running())
        p_server_->shutdown();
}