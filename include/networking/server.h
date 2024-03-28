#ifndef BATTLESHIP_SERVER_H
#define BATTLESHIP_SERVER_H
#pragma once

#include "generic_net.h"
#include "message_types.h"

namespace battleship {
class Server : public server_interface<MessageType> {
public:
    Server(uint16_t port);
};
}

#endif