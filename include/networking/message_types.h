#ifndef BATTLESHIP_MESSAGE_TYPES_H
#define BATTLESHIP_MESSAGE_TYPES_H
#pragma once

namespace battleship {
enum class MessageType : unsigned char {
    ServerAccept,
    ServerDeny,
    MessageAll,
    MessageOne,
};
}

#endif