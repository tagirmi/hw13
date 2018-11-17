#pragma once

#include <string>
#include <iostream>

namespace hw13 {

class CommandHandler
{
public:
    CommandHandler() = default;
    virtual ~CommandHandler() = default;

    void add(CommandHandler& handler)
    {
        if (m_next)
            m_next->add(handler);
        else
            m_next = &handler;
    }

    virtual std::string exec(const std::string& command)
    {
        if (m_next)
            return m_next->exec(command);

        return {};
    }

private:
    CommandHandler* m_next{};
};

class InsertHandler : public CommandHandler
{
public:
    std::string exec(const std::string& command) override
    {
        if (command.find("INSERT") != 0)
            return CommandHandler::exec(command);

        //TODO handle INSERT
        std::cout << "handle insert\n";
        return "OK\n";
    }
};

class TruncateHandler : public CommandHandler
{
public:
    std::string exec(const std::string& command) override
    {

        if (command.find("TRUNCATE") != 0)
            return CommandHandler::exec(command);

        //TODO handle TRUNCATE
        std::cout << "handle truncate\n";
        return "OK\n";
    }
};

class IntersectionHandler : public CommandHandler
{
public:
    std::string exec(const std::string& command) override
    {
        if (command.find("INTERSECTION") != 0)
            return CommandHandler::exec(command);

        //TODO handle INTERSECTION
        std::cout << "handle intersection\n";
        return "OK\n";
    }
};

class SymmetricDifferenceHandler : public CommandHandler
{
public:
    std::string exec(const std::string& command) override
    {
        if (command.find("SYMMETRIC_DIFFERENCE") != 0)
            return CommandHandler::exec(command);

        //TODO handle SYMMETRIC_DIFFERENCE
        std::cout << "handle symmetric difference\n";
        return "OK\n";
    }
};

class UnknownCommandHandler : public CommandHandler
{
public:
    std::string exec(const std::string&) override
    {
        return "ERR unknown command\n";
    }
};

} // hw13
