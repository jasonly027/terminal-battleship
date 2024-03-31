#ifndef BATTLESHIP_SERVER_H
#define BATTLESHIP_SERVER_H

#include "generic_net.h"
#include "impl/server_interface.h"
#include "message_types.h"
#include <cstddef>
#include <cstdint>
#include <memory>
#include <mutex>
#include <ostream>
#include <thread>


namespace battleship {
class Server : public server_interface<MessageType> {
public:
    explicit Server(uint16_t port, std::ostream &log = std::cout);
    virtual ~Server();

    bool run();
    bool running();
    void shutdown();

protected:
    virtual bool
        on_client_connect(std::shared_ptr<connection<MessageType>>) override;
    virtual void on_client_disconnect(
        std::shared_ptr<connection<MessageType>> client) override;
    virtual void on_message(std::shared_ptr<connection<MessageType>> client,
                            message<MessageType> &msg) override;

private:
    size_t players_;

    std::thread server_thread_;
    std::mutex muxRunning_;
    bool running_;

    using server_interface::start;
    using server_interface::stop;
};
} // namespace battleship

#endif