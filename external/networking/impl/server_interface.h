#ifndef BATTLESHIP_SERVER_INTERFACE_H
#define BATTLESHIP_SERVER_INTERFACE_H
#pragma once

#include "connection.h"
#include "message.h"
#include "tsqueue.h"
#include <asio.hpp>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <exception>
#include <iostream>
#include <memory>
#include <system_error>
#include <thread>

namespace battleship {
template <typename T> class server_interface {
public:
    server_interface(uint16_t port)
        : acceptor_(ctx_, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {}

    virtual ~server_interface() { stop(); }

    // [ASYNC] Start server
    bool start() {
        try {
            wait_for_client_connection();
            thread_ctx_ = std::thread([this]() { ctx_.run(); });
        } catch (std::exception &e) {
            std::cerr << "[SERVER] Exception: " << e.what() << '\n';
            return false;
        }

        std::cout << "[SERVER] Started\n";
        return true;
    }

    // [ASYNC] Stop client
    void stop() {
        ctx_.stop();

        if (thread_ctx_.joinable())
            thread_ctx_.join();

        std::cout << "[SERVER] Stopped\n";
    }

    // [ASYNC] Wait for a client to connect
    void wait_for_client_connection() {
        acceptor_.async_accept([this](std::error_code ec,
                                      asio::ip::tcp::socket socket) {
            if (!ec) {
                std::cout << "[SERVER] New Connection: "
                          << socket.remote_endpoint() << '\n';

                // Create connection
                std::shared_ptr<connection<T>> new_conn =
                    std::make_shared<connection<T>>(
                        connection<T>::owner::server, ctx_, std::move(socket),
                        messages_in_);

                // Possible validation point
                if (on_client_connect(new_conn)) {
                    connections_.push_back(std::move(new_conn));

                    connections_.back()->connect_to_client(id_counter_++);

                    std::cout << "[" << connections_.back()->id()
                              << "] Connection Approved\n";
                } else {
                    std::cout << "[-----] Connection Denied\n";
                }

            } else {
                std::cout << "[SERVER] New Connection error: " << ec.message()
                          << '\n';
            }

            // Wait for next client to connect
            wait_for_client_connection();
        });
    }

    // [ASYNC] Message a specific client
    void message_client(std::shared_ptr<connection<T>> client,
                        const message<T> &msg) {
        if (client && client->connected()) {
            client->send(msg);
        // If client had disconnected, remove them from
        // connections list
        } else {
            on_client_disconnect(client);
            client.reset();
            connections_.erase(
                std::remove(connections_.begin(), connections_.end(), client),
                connections_.end());
        }
    }

    // [ASYNC] Message all clients, optionally, do not message
    // one client
    void message_all_client(
        const message<T> &msg,
        std::shared_ptr<connection<T>> p_ignore_client = nullptr) {
        bool invalid_client_exists = false;

        for (auto &client : connections_) {
            if (client && client->connected()) {
                if (client != p_ignore_client)
                    client->send(msg);
            // If client had disconnected, mark them
            // for removal from connections list
            } else {
                on_client_disconnect(client);
                client.reset();
                invalid_client_exists = true;
            }
        }

        // Remove any disconnected clients from connections list
        if (invalid_client_exists)
            connections_.erase(
                std::remove(connections_.begin(), connections_.end(), nullptr),
                connections_.end());
    }


    // Update there are new messages in the incoming queue,
    // handle them
    void update(size_t max_messages = -1, bool waiting = true) {
        // Optionally, can sleep until new messages arrive
        if (waiting)
            messages_in_.wait();

        size_t message_count = 0;
        while (message_count < max_messages && !messages_in_.empty()) {
            auto msg = messages_in_.pop_front();

            on_message(msg.remote, msg.msg);

            ++message_count;
        }
    }

protected:
    // The following three methods should be implemented by a concrete server
    virtual bool on_client_connect(std::shared_ptr<connection<T>> client) {
        return false;
    }

    virtual void on_client_disconnect(std::shared_ptr<connection<T>> client) {}

    virtual void on_message(std::shared_ptr<connection<T>> client,
                            message<T> &msg) {}

    tsqueue<owned_message<T>> messages_in_;
    std::deque<std::shared_ptr<connection<T>>> connections_;
    asio::io_context ctx_;
    std::thread thread_ctx_;
    asio::ip::tcp::acceptor acceptor_;
    uint32_t id_counter_ = 10000;
};
} // namespace battleship

#endif