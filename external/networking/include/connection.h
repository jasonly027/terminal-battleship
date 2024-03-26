#ifndef BATTLESHIP_CONNECTION_H
#define BATTLESHIP_CONNECTION_H
#pragma once

#include "asio/io_context.hpp"
#include "asio/ip/tcp.hpp"
#include "message.h"
#include "tsqueue.h"
#include <memory>

namespace battleship {
template <typename T> struct message;
template <typename T> struct owned_message;

template <typename T>
class connection : public std::enable_shared_from_this<connection<T>> {
public:
    connection() {}
    virtual ~connection() {}

    bool connect_to_server();
    bool disconnect();
    bool connected() const;

    bool send(const message<T> &msg);
protected:
    asio::ip::tcp::socket socket_;
    asio::io_context &ctx_;
    tsqueue<message<T>> messages_out_;
    tsqueue<owned_message<T>> &messages_in;
};
} // namespace battleship

#endif