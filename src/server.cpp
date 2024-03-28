#include "generic_net.h"
#include <cstdint>
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
        battleship::message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::ServerAccept;
        client->send(msg);
        return true;
    }

    virtual void on_client_disconnect(
        std::shared_ptr<battleship::connection<CustomMsgTypes>> client)
        override {
            std::cout << "Removing client [" << client->id() << "]\n";
        }

    virtual void
    on_message(std::shared_ptr<battleship::connection<CustomMsgTypes>> client,
               battleship::message<CustomMsgTypes> &msg) override {
        switch (msg.header.id) {
        case CustomMsgTypes::ServerPing: {
            std::cout << "[" << client->id() << "]: Server Ping\n";
            int str;
            msg >> str;
            std::cout << "Msg was: " << str << '\n';

            client->send(msg);
        } break;
        case CustomMsgTypes::MessageAll: {
            std::cout << "[" << client->id() << "]: Message All\n";
            battleship::message<CustomMsgTypes> msg;
            msg.header.id = CustomMsgTypes::ServerMessage;
            msg << client->id();
            message_all_client(msg, client);
        }
        }
    }
};

int main() {
    CustomServer server(49494);
    server.start();

    while (1) {
        server.update(-1, true);
    }

    return 0;
}