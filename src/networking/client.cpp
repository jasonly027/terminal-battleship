#include "client.h"
#include "message_factory.h"

using namespace battleship;

Client::Client(std::ostream &log) : client_interface(log)  {}

void Client::ping() {
    send(Msg::Ping());
}