#include <iostream>
#include <thread>

#include <asio.hpp>

#include "server.h"

hw13::Server::Server(uint16_t port)
    : m_port{port}
{
}

void hw13::Server::run()
{
    asio::io_service service;
    asio::ip::tcp::endpoint ep{asio::ip::tcp::v4(), m_port};
    asio::ip::tcp::acceptor acc{service, ep};

    while(true) {
        auto sock = asio::ip::tcp::socket{service};

        acc.accept(sock);
        std::thread{[](auto&& sock) {
            while (true) {
                try {
                    char data[4];
                    size_t len = sock.read_some(asio::buffer(data));
                    std::cout << "receive " << len << "=" << std::string{data, len} << std::endl;
                    asio::write(sock, asio::buffer("pong", 4));
                }
                catch (const std::exception &e) {
                    std::cerr << e.what() << std::endl;
                    break;
                }
            }

        }, std::move(sock)}.detach();
    }
}
