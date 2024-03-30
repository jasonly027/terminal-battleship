#ifndef BATTLESHIP_MESSAGE_FACTORY_H
#define BATTLESHIP_MESSAGE_FACTORY_H
#pragma once

#include "generic_net.h"
#include "message_types.h"

namespace battleship {
namespace Msg{
    inline message<MessageType> ServerShutdown() {
        return message(MessageType::ServerShutdown);
    }

    inline message<MessageType> Ping() {
        return message(MessageType::Ping);
    }

    inline message<MessageType> FullLobby() {
        return message(MessageType::FullLobby);
    }
}
}

#endif