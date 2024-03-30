#include "server.h"
#include "message_factory.h"
#include "message_types.h"
#include <cstdint>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>

using namespace battleship;

Server::Server(uint16_t port, std::ostream &log)
    : server_interface(port, log), running_(false) {}

bool Server::run() {
    muxRunning_.lock();
    running_ = start();
    muxRunning_.unlock();

    if (running()) {
        server_thread_ = std::thread([this]() {
            while (running()) {
                update();
            }
        });
        return true;
    }

    return running();
}

bool Server::running() {
    std::scoped_lock<std::mutex> lock(muxRunning_);
    return running_;
}

void Server::shutdown() {
    if (!running())
        return;

    muxRunning_.lock();
    running_ = false;
    muxRunning_.unlock();
    messages_in_.push_back({nullptr, Msg::ServerShutdown()});

    if (server_thread_.joinable())
        server_thread_.join();
}

bool Server::on_client_connect(
    std::shared_ptr<connection<MessageType>> client) {
    log_ << "[SERVER] Client Join\n";
    if (connections_.size() >= kMaxPlayers) {
        message_client(client, Msg::FullLobby());
        return false;
    }
    return true;
}

void Server::on_client_disconnect(
    std::shared_ptr<connection<MessageType>> client) {
    log_ << "[SERVER] Client Left\n";
}

void Server::on_message(std::shared_ptr<connection<MessageType>> client,
                        message<MessageType> &msg) {
    log_ << "[SERVER] Message Received\n";
    switch (msg.kind()) {
    case MessageType::Ping: {
        std::ostringstream oss;
        oss << "[SERVER] [" << client->id() << "] Pinged\n";
        log_ << oss.str();
        message_client(client, Msg::Ping());
    }
    case MessageType::ServerShutdown: {
        stop();
    }
    }
}