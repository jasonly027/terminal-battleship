#ifndef BATTLESHIP_CONNECTION_H
#define BATTLESHIP_CONNECTION_H
#pragma once

#include "message.h"
#include "tsqueue.h"
#include <asio.hpp>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>
#include <system_error>


namespace battleship {
template <typename T> struct message_header;
template <typename T> struct message;
template <typename T> struct owned_message;

template <typename T>
class connection : public std::enable_shared_from_this<connection<T>> {
public:
    enum class owner { server, client };

    connection(owner parent, asio::io_context &ctx,
               asio::ip::tcp::socket socket,
               tsqueue<owned_message<T>> &messages_in)
        : ctx_(ctx), socket_(std::move(socket)), messages_in(messages_in) {
        owner_type_ = parent;
    }

    virtual ~connection() {}

    // Get id
    uint32_t id() const { return id_; }

    // Connect with client, owner of this connection must be a server
    void connect_to_client(uint32_t uid = 0) {
        if (owner_type_ == owner::server) {
            if (socket_.is_open()) {
                id_ = uid;
                // Prime the read header function
                read_header();
            }
        }
    }

    // [ASYNC] Connect with server, owner of this connection must be a client
    void
    connect_to_server(const asio::ip::tcp::resolver::results_type &endpoints) {
        if (owner_type_ == owner::client) {
            asio::async_connect(
                socket_, endpoints,
                [this](std::error_code ec, asio::ip::tcp::endpoint endpoint) {
                    if (!ec) {
                        // Prepare client to read an incoming header
                        read_header();
                    }
                });
        }
    }

    // [ASYNC] Disconnect
    void disconnect() {
        if (connected())
            asio::post(ctx_, [this]() { socket_.close(); });
    }

    // Check if connected (check if socket is open)
    bool connected() const { return socket_.is_open(); }

    // [ASYNC] Send a message
    void send(const message<T> &msg) {
        asio::post(ctx_, [this, msg]() {
            bool is_writing_message = !messages_out_.empty();
            messages_out_.push_back(msg);
            // If a message is currently being written, there is
            // no need to call the write header function. This
            // message will automatically be written when the
            // message queue gets to it
            //
            // If no message is currently being written, i.e.,
            // the message queue is empty, we must indicate
            // there is work to do by calling the write header
            // function
            if (!is_writing_message)
                write_header();
        });
    }

private:
    // [ASYNC] Wait for a message header to arrive and read it
    void read_header() {
        asio::async_read(
            socket_,
            asio::buffer(&msg_temporary_in_.header, sizeof(message_header<T>)),
            [this](std::error_code ec, std::size_t length) {
                if (!ec) {
                    // If the header indicates the next piece of data
                    // is its body, prepare to read it
                    if (msg_temporary_in_.header.size > 0) {
                        msg_temporary_in_.body.resize(
                            msg_temporary_in_.header.size);
                        read_body();
                    // Otherwise complete this message transfer
                    // by moving this message to the incoming queue
                    } else {
                        add_to_incoming_message_queue();
                    }
                } else {
                    std::cout << "[" << id_ << "] Read Header Fail\n";
                    std::cout << ec.message() << '\n';
                    socket_.close();
                }
            });
    }

    // [ASYNC] Wait for a message body to arrive and read it
    void read_body() {
        asio::async_read(socket_,
                         asio::buffer(msg_temporary_in_.body.data(),
                                      msg_temporary_in_.body.size()),
                         [this](std::error_code ec, std::size_t length) {
                             // Complete this message transfer
                             // by moving this message to the incoming queue
                             if (!ec) {
                                 add_to_incoming_message_queue();
                             } else {
                                 std::cout << "[" << id_
                                           << "] Read Body Fail\n"
                                           << ec.message();
                                 socket_.close();
                             }
                         });
    }

    // [ASYNC] Write the header in the out queue
    void write_header() {
        asio::async_write(socket_,
                          asio::buffer(&messages_out_.front().header,
                                       sizeof(message_header<T>)),
                          [this](std::error_code ec, std::size_t length) {
                              if (!ec) {
                                  // If the header indicates it has a body,
                                  // write it as well
                                  if (messages_out_.front().body.size() > 0) {
                                      write_body();
                                  // Otherwise, complete this message transfer
                                  // by removing it from the out queue and writing
                                  // the next message, if it exists.
                                  } else {
                                      messages_out_.pop_front();

                                      if (!messages_out_.empty()) {
                                          write_header();
                                      }
                                  }
                              } else {
                                  std::cout << "[" << id_
                                            << "] Write Header Fail\n"
                                            << ec.message();
                                  socket_.close();
                              }
                          });
    }

    // [ASYNC] Write the body in the out queue
    void write_body() {
        asio::async_write(socket_,
                          asio::buffer(messages_out_.front().body.data(),
                                       messages_out_.front().body.size()),
                          [this](std::error_code ec, std::size_t length) {
                              if (!ec) {
                                  // Complete this message transfer
                                  // by removing it from the out queue and writing
                                  // the next message, if it exists.
                                  messages_out_.pop_front();

                                  if (!messages_out_.empty()) {
                                      write_header();
                                  }
                              } else {
                                  std::cout << "[" << id_
                                            << "] Write Body Fail\n";
                                  socket_.close();
                              }
                          });
    }

    // Add the newly transferred message to the incoming queue
    void add_to_incoming_message_queue() {
        // If the owner of this connection is the server,
        // keep track of the connection to know the client
        if (owner_type_ == owner::server)
            messages_in.push_back(
                {this->shared_from_this(), msg_temporary_in_});
        else
            messages_in.push_back({nullptr, msg_temporary_in_});

        read_header();
    }

protected:
    asio::ip::tcp::socket socket_;
    asio::io_context &ctx_;
    tsqueue<message<T>> messages_out_;
    tsqueue<owned_message<T>> &messages_in;
    message<T> msg_temporary_in_;

    owner owner_type_ = owner::server;
    uint32_t id_ = 0;
};
} // namespace battleship

#endif