#ifndef BATTLESHIP_MESSAGE_H
#define BATTLESHIP_MESSAGE_H
#pragma once

#include "connection.h"
#include <cstdint>
#include <memory>
#include <vector>

namespace battleship {
template <typename T> struct message_header {
    T id();
    uint32_t size = 0;
};

template <typename T> struct message {
    message_header<T> header{};
    std::vector<uint8_t> body;

    // Return size of message packet in bytes
    size_t size() const { return sizeof(message_header<T>) + body.size(); }
};

template <typename T> class connection;
template <typename T> struct owned_message {
    std::shared_ptr<connection<T>> remote = nullptr;
    message<T> msg;
};
} // namespace battleship

#endif