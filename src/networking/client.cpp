#include "client.h"
#include "message_types.h"

using namespace battleship;

void Client::ping() {
    message<MessageType> msg;
    msg.header.id = MessageType::Ping;
    send(msg);
}