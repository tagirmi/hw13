#pragma once

#include <string>
#include <iostream>
#include <sstream>

#include "database.h"
#include "util.h"

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

protected:
    std::string ok()
    {
        return "OK\n";
    }

    std::string ok(const Database::Result& result)
    {
        std::stringstream ss;
        for (const auto& i : result)
            ss << i << "\n";
        ss << "OK\n";
        return ss.str();
    }

    std::string error(const std::string& message)
    {
        return "ERR " + message + "\n";
    }

    std::vector<std::string> parseArgs(const std::string& command)
    {
        return util::split(command, ' ');
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

        auto args = parseArgs(command);

        if (args.size() != 4)
            return error("Неверное количество аргументов");

        int id{};
        std::string parseError;
        if (!parseId(args[2], id, parseError))
            return error(parseError);

        auto& db = Database::instance();

        if (!db.insert(args[1], std::make_tuple(id, args[3])))
            return error(db.getError());

        return ok();
    }

private:
    bool parseId(const std::string& id, int& parsed, std::string& error)
    {
        try
        {
            parsed = std::stoi(id);
        }
        catch(const std::invalid_argument&)
        {
            error = "Аргумент ID неверного типа";
            return false;
        }
        catch(const std::out_of_range&)
        {
            error = "Невозможно преобразовать аргумент ID в число";
            return false;
        }
        return true;
    }
};

class TruncateHandler : public CommandHandler
{
public:
    std::string exec(const std::string& command) override
    {

        if (command.find("TRUNCATE") != 0)
            return CommandHandler::exec(command);

        auto args = parseArgs(command);

        if (args.size() != 2)
            return error("Неверное количество аргументов");

        auto& db = Database::instance();

        if (!db.truncate(args[1]))
            return error(db.getError());

        return ok();
    }
};

class IntersectionHandler : public CommandHandler
{
public:
    std::string exec(const std::string& command) override
    {
        if (command.find("INTERSECTION") != 0)
            return CommandHandler::exec(command);

        auto args = parseArgs(command);

        if (args.size() > 1)
            return error("Аргументы не ожидаются");

        auto& db = Database::instance();

        if (!db.intersection())
            return error(db.getError());

        return ok(db.getResult());
    }
};

class SymmetricDifferenceHandler : public CommandHandler
{
public:
    std::string exec(const std::string& command) override
    {
        if (command.find("SYMMETRIC_DIFFERENCE") != 0)
            return CommandHandler::exec(command);

        auto args = parseArgs(command);

        if (args.size() > 1)
            return error("Аргументы не ожидаются");

        auto& db = Database::instance();

        if (!db.symmetric_difference())
            return error(db.getError());

        return ok(db.getResult());
    }
};

class UnknownCommandHandler : public CommandHandler
{
public:
    std::string exec(const std::string&) override
    {
        return error("Неопознанная команда");
    }
};

} // hw13
