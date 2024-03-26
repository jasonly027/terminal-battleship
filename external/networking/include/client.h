#ifndef BATTLESHIP_CLIENT_H
#define BATTLESHIP_CLIENT_H
#include <exception>
#include <iostream>
#pragma once

#include "asio/io_context.hpp"
#include "asio/ip/tcp.hpp"
#include "message.h"
#include "tsqueue.h"
#include <cstdint>
#include <memory>
#include <string>
#include <thread>

namespace battleship {
template <typename T> class client_interface {
public:
    client_interface() : socket_(ctx_) {}

    virtual ~client_interface() { disconnect(); }

    bool connect(const std::string &host, const uint16_t port) {
        try {
            connection_ = std::make_unique < connection<T>();
            asio::ip::tcp::resolver resolver(ctx_);
            endpoints_ = resolver.resolve(host, std::to_string(port));
            connection_->connect_to_server(endpoints_);

            thread_ctx_ = std::thread([this]() { ctx_.run(); })
        } catch (std::exception &e) {
            std::cerr << "Client Exception: " << e.what() << '\n';
            return false;
        }
        return true;
    }

    void disconnect() {
        if (connected()) {
            connection_->disconnect();
        }
        ctx_.stop();
        if (thread_ctx_.joinable())
            thread_ctx_.join();

        connection_.release();
    }

    bool connected() {
        if (connection_)
            connection_->connected();
        else
            return false;
    }

    tsqueue<owned_message<T>> &incoming() { return messages_in_; }

protected:
    asio::io_context ctx_;
    std::thread thread_ctx_;
    asio::ip::tcp::socket socket_;
    std::unique_ptr<connection<T>> connection_;

private:
    tsqueue<owned_message<T>> messages_in_;
};
} // namespace battleship

#endif