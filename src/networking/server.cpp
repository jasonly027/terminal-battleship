#include "server.h"
#include <cstdint>

using namespace battleship;

Server::Server(uint16_t port) : server_interface(port) {}