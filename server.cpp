#include <iostream>
#include <thread>
#include <vector>

#include <asio.hpp>

#include "server.h"
#include "command_handler.h"

namespace {

std::vector<std::string> split(std::string& str, char d = '\n')
{
    std::vector<std::string> r;
    r.reserve(std::count(str.cbegin(), str.cend(), d) + 1);

    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos) {
        r.emplace_back(str.substr(0, stop));
        str.erase(0, stop + 1);

        stop = str.find_first_of(d);
    }

    return r;
}

}

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
            std::string str;
            CommandHandler handler;
            InsertHandler insert;
            TruncateHandler truncate;
            IntersectionHandler intersection;
            SymmetricDifferenceHandler symmetricDifference;
            UnknownCommandHandler unknown;

            handler.add(insert);
            handler.add(truncate);
            handler.add(intersection);
            handler.add(symmetricDifference);
            handler.add(unknown);

            while (true) {
                try {
                    char data[256];
                    size_t len = sock.read_some(asio::buffer(data));
                    str += std::string{data, len};

                    auto lines = split(str);

                    if (lines.empty())
                        continue;

                    for (const auto& i : lines) {
                        handler.exec(i);
                    }
                }
                catch (const std::exception &e) {
                    std::cerr << e.what() << std::endl;
                    break;
                }
            }

        }, std::move(sock)}.detach();
    }
}
