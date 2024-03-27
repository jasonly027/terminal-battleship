#include "message.h"
#include "server_interface.h"
#include <iostream>

enum class CustomMsgTypes : uint32_t {
    ServerAccept,
    ServerDeny,
    ServerPing,
    MessageAll,
    ServerMessage
};

class CustomServer : public battleship::server_interface<CustomMsgTypes> {
public:
    CustomServer(uint16_t port)
        : battleship::server_interface<CustomMsgTypes>(port) {}

protected:
    virtual bool on_client_connect(
        std::shared_ptr<battleship::connection<CustomMsgTypes>> client)
        override {
        return true;
    }

    virtual void on_client_disconnect(
        std::shared_ptr<battleship::connection<CustomMsgTypes>> client)
        override {}

    virtual void
    on_message(std::shared_ptr<battleship::connection<CustomMsgTypes>> client,
               battleship::message<CustomMsgTypes> &msg) override {
                switch (msg.header.id) {
                case CustomMsgTypes::ServerPing:
                    {
                        std::cout << "[" << client->id() << "]: Server Ping\n";

                        client->send(msg);
                    }
                }
               }
};

int main() {
    CustomServer server(49494);
    server.start();

    while (1) {
        server.update();
    }

    return 0;
}