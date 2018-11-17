#include <iostream>

#include "server.h"

namespace {

bool parseArg(int argc, char* argv[], uint16_t& parsed)
{
    if (argc < 2) {
        std::cerr << "command line argument expected; usage: join_server <port> (1..65535)";
        return false;
    }

    try
    {
        int arg = std::stoi(argv[1]);
        if (parsed < 1 || parsed > 65535) {
            std::cerr << "invalid argument <port>";
            return false;
        }
        parsed = static_cast<uint16_t>(arg);
    }
    catch(const std::invalid_argument&)
    {
        std::cerr << "invalid argument passed to command line";
        return false;
    }
    catch(const std::out_of_range&)
    {
        std::cerr << "didn't convert argument to number";
        return false;
    }

    return true;
}

}

int main(int argc, char *argv[])
{
    uint16_t port;
    if (!parseArg(argc, argv, port))
        return 1;

    try {
        hw13::Server server{port};
        server.run();
    }
    catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
