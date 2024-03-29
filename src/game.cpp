#include "game.h"
#include "server.h"
#include <memory>
#include <thread>

using namespace battleship;

void Game::start_server() {
    p_server_ = std::make_unique<Server>(49494);
    server_thread_ = std::thread([this](){
        p_server_->start();
    });
}