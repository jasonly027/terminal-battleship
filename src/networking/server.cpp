#include "server.h"
#include "game.h"
#include "generic_net.h"
#include "message_factory.h"
#include "message_types.h"
#include <cstdint>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>

using namespace battleship;

Server::Server(uint16_t port, std::ostream &log)
    : server_interface(port, log), running_(false), players_(0) {}

Server::~Server() { shutdown(); }

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
    if (players_ >= Game::kMaxPlayers) {
        log_ << "[SERVER] Connection Denied\n";
        return false;
    }

    connections_.push_back(std::move(client));
    connections_.back()->connect_to_client(id_counter_++);

    ++players_;
    message_all_client(Msg::LobbyStatus(players_));
    if (players_ == Game::kMaxPlayers) {
        message_all_client(Msg::StartingGame());
    }

    std::ostringstream oss;
    oss << "[SERVER] Approved [" << connections_.back()->id() << "]\n";
    log_ << oss.str();

    return true;
}

void Server::on_client_disconnect(
    std::shared_ptr<connection<MessageType>> client) {
    --players_;

    std::ostringstream oss;
    oss << "[SERVER] [" << client->id() << "] disconnected\n";
    log_ << oss.str();
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
    } break;
    case MessageType::ServerShutdown: {
        stop();
    } break;
    case MessageType::ServerAccept:
    case MessageType::ServerDeny:
    case MessageType::MessageAll:
    case MessageType::MessageOne:
    case MessageType::FullLobby:
    case MessageType::LobbyStatus:
    case MessageType::StartingGame:
        break;
    }
}