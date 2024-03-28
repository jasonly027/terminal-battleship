#include "server.h"
#include <cstdint>
#include <iostream>
#include <memory>

using namespace battleship;

Server::Server(uint16_t port) : server_interface(port) {}

bool Server::on_client_connect(std::shared_ptr<connection<MessageType>> client) {
    std::cout << "Client is here\n";
    return true;
}

void Server::on_client_disconnect(std::shared_ptr<connection<MessageType>> client) {
    std::cout << "Client left\n";
}

void Server::on_message(std::shared_ptr<connection<MessageType>> client, message<MessageType> &msg) {

}