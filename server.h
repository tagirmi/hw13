#pragma once

namespace hw13 {

class Server {
public:
    explicit Server(uint16_t port);

    void run();

private:
    uint16_t m_port;
};

} // hw13
