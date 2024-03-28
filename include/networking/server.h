#ifndef BATTLESHIP_SERVER_H
#define BATTLESHIP_SERVER_H
#pragma once

#include "generic_net.h"
#include "message_types.h"
#include <memory>

namespace battleship {
class Server : public server_interface<MessageType> {
public:
    Server(uint16_t port);

protected:
    virtual bool
        on_client_connect(std::shared_ptr<connection<MessageType>>) override;
    virtual void on_client_disconnect(
        std::shared_ptr<connection<MessageType>> client) override;
    virtual void on_message(std::shared_ptr<connection<MessageType>> client,
                            message<MessageType> &msg) override;
};
} // namespace battleship

#endif