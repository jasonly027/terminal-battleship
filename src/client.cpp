#include "generic_net.h"
#include <asio.hpp>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <string>

enum class CustomMsgTypes : uint32_t {
    ServerAccept,
    ServerDeny,
    ServerPing,
    MessageAll,
    ServerMessage
};

class CustomClient : public battleship::client_interface<CustomMsgTypes> {
public:
    void PingServer() {
        battleship::message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::ServerPing;

        int num = 420;
        msg << num;
        std::cout << "About to ping\n";
        send(msg);
    }

    void MessageAll() {
        battleship::message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::MessageAll;
        send(msg);
    }
};

int main() {
    CustomClient c;
    c.connect("127.0.0.1", 49494);

    constexpr auto duration = std::chrono::seconds(2);
    auto lastTime = std::chrono::steady_clock::now();
    while (true) {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = currentTime - lastTime;
        if (elapsedTime >= duration) {
            lastTime = currentTime;
            c.PingServer();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        if (c.connected()) {
            if (!c.incoming().empty()) {

                auto msg = c.incoming().pop_front().msg;

                switch (msg.header.id) {
                case CustomMsgTypes::ServerAccept: {
                    // Server has responded to a ping request
                    std::cout << "Server Accepted Connection\n";
                } break;
                case CustomMsgTypes::ServerPing: {
                    // Server has responded to a ping request
                    std::cout << "Server pong\n";
                } break;
                }
            }
        }
    }

    return 0;
}