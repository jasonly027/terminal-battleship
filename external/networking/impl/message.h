#ifndef BATTLESHIP_MESSAGE_H
#define BATTLESHIP_MESSAGE_H
#pragma once

#include "connection.h"
#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

namespace battleship {
template <typename T> struct message_header {
    // T will be an enum indicating the kind of message
    T id{};
    // How many bytes in the body
    uint32_t size = 0;
};

template <typename T> struct message {
    message_header<T> header{};
    std::vector<uint8_t> body;

    // Get how many bytes the body is
    size_t size() const { return body.size(); }

    friend std::ostream &operator<<(std::ostream &os, const message<T> &msg) {
        os << "ID:" << int(msg.header.id) << " Size:" << msg.header.size
           << '\n';
        return os;
    }

    // Insert data into body
    template <typename DataType>
    friend message<T> &operator<<(message<T> &msg, const DataType &data) {
        static_assert(std::is_standard_layout<DataType>::value,
                      "Data is too complex to be pushed into vector");

        size_t i = msg.body.size();
        msg.body.resize(msg.body.size() + sizeof(DataType));
        std::memcpy(msg.body.data() + i, &data, sizeof(DataType));
        msg.header.size = msg.size();

        return msg;
    }

    // Extract data from body
    template <typename DataType>
    friend message<T> &operator>>(message<T> &msg, DataType &data) {
        static_assert(std::is_standard_layout<DataType>::value,
                      "Data is too complex to be pulled from vector");

        size_t i = msg.body.size() - sizeof(DataType);
        std::memcpy(&data, msg.body.data() + i, sizeof(DataType));
        msg.body.resize(i);
        msg.header.size = msg.size();
        return msg;
    }
};

template <typename T> class connection;
template <typename T> struct owned_message {
    std::shared_ptr<connection<T>> remote = nullptr;
    message<T> msg;

    friend std::ostream &operator<<(std::ostream &os,
                                    const owned_message<T> &msg) {
        os << msg.msg;
        return os;
    }
};
} // namespace battleship

#endif