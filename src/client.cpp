#include "client_interface.h"
#include "message.h"
#include <asio.hpp>
#include <chrono>
#include <iostream>

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

        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();

        msg << timeNow;
        send(msg);
    }
};

int main() {
    CustomClient c;
    c.connect("localhost", 49494);

    bool key[3] = {false, false, false};
    bool old_key[3] = {false, false, false};

    bool bQuit = false;
    while (!bQuit) {
        if (GetForegroundWindow() == GetConsoleWindow()) {
            key[0] = GetAsyncKeyState('1') & 0x8000;
            key[1] = GetAsyncKeyState('2') & 0x8000;
            key[2] = GetAsyncKeyState('3') & 0x8000;
        }

        if (key[0] && !old_key[0])
            c.PingServer();
        if (key[2] && !old_key[2])
            bQuit = true;

        for (int i = 0; i < 3; i++)
            old_key[i] = key[i];

        if (c.connected()) {
            if (!c.incoming().empty()) {

                auto msg = c.incoming().pop_front().msg;

                switch (msg.header.id) {
                case CustomMsgTypes::ServerPing: {
                    // Server has responded to a ping request
                    std::chrono::system_clock::time_point timeNow =
                        std::chrono::system_clock::now();
                    std::chrono::system_clock::time_point timeThen;
                    msg >> timeThen;
                    std::cout
                        << "Ping: "
                        << std::chrono::duration<double>(timeNow - timeThen)
                               .count()
                        << "\n";
                } break;
                }
            }
        } else {
            std::cout << "Server Down\n";
            bQuit = true;
        }
    }

    return 0;
}