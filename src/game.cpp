#include "game.h"
#include "server.h"
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>


using namespace battleship;

void Game::host_game() {
    std::cout << "Enter Port\n"
                 "> ";
    // const uint16_t port = util::get_input<uint16_t>();
    const uint16_t port = 49494;

    if (!start_server(port)) {
        std::cout << "Error starting server...\n";
        std::exit(-1);
    }

    if (!start_client("127.0.0.1", port)) {
        std::cout << "Error joining hosted server...\n";
        std::exit(-1);
    }
}

void Game::join_game() {
    bool client_started = false;
    do {
        std::cout << "\nEnter Hostname\n"
                     "> ";
        // const std::string hostname = util::get_input<std::string>();
        std::cout << "Enter Port\n"
                     "> ";
        // const uint16_t port = util::get_input<uint16_t>();
        const std::string hostname = "127.0.0.1";
        const uint16_t port = 49494;

        client_started = start_client(hostname, port);
        if (!client_started) {
            std::cout << "Failed to connect...\n";
        }
    } while (!client_started);
}

void Game::play() {
    if (p_client_) {
        p_client_->listen();
    }
}

bool Game::start_server(uint16_t port) {
    p_server_ = std::make_unique<Server>(port);
    if (p_server_->run()) {
        return true;
    }

    p_server_.reset();
    return false;
}

void Game::stop_server() { p_server_->shutdown(); }

bool Game::start_client(const std::string &host, uint16_t port) {
    p_client_ = std::make_unique<Client>();
    return p_client_->connect(host, port);
}

void Game::stop_client() { p_client_->disconnect(); }