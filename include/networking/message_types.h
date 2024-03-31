#ifndef BATTLESHIP_MESSAGE_TYPES_H
#define BATTLESHIP_MESSAGE_TYPES_H

namespace battleship {
enum class MessageType : unsigned char {
    ServerShutdown,
    ServerAccept,
    ServerDeny,
    Ping,
    MessageAll,
    MessageOne,
    FullLobby,
    LobbyStatus,
    StartingGame,
};
}

#endif