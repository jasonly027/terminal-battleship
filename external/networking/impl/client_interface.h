#ifndef BATTLESHIP_CLIENT_INTERFACE_H
#define BATTLESHIP_CLIENT_INTERFACE_H
#pragma once

#include "message.h"
#include "tsqueue.h"
#include <asio.hpp>
#include <cstdint>
#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

namespace battleship {
template <typename T> class client_interface {
public:
    client_interface() {}

    virtual ~client_interface() { disconnect(); }

    // [ASYNC] Connect client
    bool connect(const std::string &host, const uint16_t port) {
        try {
            // Resolve hostname and port to an endpoint
            asio::ip::tcp::resolver resolver(ctx_);
            asio::ip::tcp::resolver::results_type endpoints =
                resolver.resolve(host, std::to_string(port));

            // Create connection
            connection_ = std::make_unique<connection<T>>(
                connection<T>::owner::client, ctx_, asio::ip::tcp::socket(ctx_),
                messages_in_);

            // Connect to server
            connection_->connect_to_server(endpoints);

            // Move subsequent connection work to independent thread
            thread_ctx_ = std::thread([this]() { ctx_.run(); });
        } catch (std::exception &e) {
            std::cerr << "Client Exception: " << e.what() << '\n';
            return false;
        }
        return true;
    }

    // [ASYNC] Disconnect client
    void disconnect() {
        if (connected()) {
            connection_->disconnect();
        }
        ctx_.stop();
        if (thread_ctx_.joinable())
            thread_ctx_.join();

        connection_.release();
    }

    // Check if connected (check if socket is open)
    bool connected() {
        if (connection_)
            return connection_->connected();
        else
            return false;
    }

    // [ASYNC] Send a message
    void send(const message<T> &msg) {
        if (connected()) {
            connection_->send(msg);
        }
    }

    // Get incoming message queue
    tsqueue<owned_message<T>> &incoming() { return messages_in_; }

protected:
    asio::io_context ctx_;
    std::thread thread_ctx_;
    std::unique_ptr<connection<T>> connection_;

private:
    tsqueue<owned_message<T>> messages_in_;
};
} // namespace battleship

#endif