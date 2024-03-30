#ifndef BATTLESHIP_CLIENT_H
#define BATTLESHIP_CLIENT_H
#pragma once

#include "generic_net.h"
#include "message_types.h"

namespace battleship {
class Client : public client_interface<MessageType> {
public:
    explicit Client(std::ostream &log = std::cout);
    void ping();
};
} // namespace battleship

#endif