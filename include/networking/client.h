#ifndef BATTLESHIP_CLIENT_H
#define BATTLESHIP_CLIENT_H
#include "impl/client_interface.h"
#include "impl/message.h"
#include "networking/message_types.h"
#pragma once

#include "generic_net.h"

namespace battleship {
class Client : public client_interface<MessageType> {
public:
    void ping();
};
} // namespace battleship

#endif