#ifndef BATTLESHIP_MESSAGE_FACTORY_H
#define BATTLESHIP_MESSAGE_FACTORY_H

#include "generic_net.h"
#include "message_types.h"
#include <cstddef>


namespace battleship {
namespace Msg {
inline message<MessageType> ServerShutdown() {
    return message(MessageType::ServerShutdown);
}

inline message<MessageType> Ping() { return message(MessageType::Ping); }

inline message<MessageType> FullLobby() {
    return message(MessageType::FullLobby);
}

inline message<MessageType> LobbyStatus(size_t num_players) {
    message<MessageType> msg(MessageType::LobbyStatus);
    msg << num_players;
    return msg;
}

inline message<MessageType> StartingGame() {
    return message(MessageType::StartingGame);
}
} // namespace Msg
} // namespace battleship

#endif