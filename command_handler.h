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

  virtual void exec(const std::string& command)
  {
    if (m_next)
      m_next->exec(command);
  }

private:
  CommandHandler* m_next{};
};

class InsertHandler : public CommandHandler
{
public:
  void exec(const std::string& command) override
  {
    if (command.find("INSERT") != 0) {
      CommandHandler::exec(command);
      return;
    }

    //TODO handle INSERT
    std::cout << "handle insert\n";
  }
};

class TruncateHandler : public CommandHandler
{
public:
  void exec(const std::string& command) override
  {
    if (command.find("TRUNCATE") != 0) {
      CommandHandler::exec(command);
      return;
    }

    //TODO handle TRUNCATE
      std::cout << "handle truncate\n";
  }
};

class IntersectionHandler : public CommandHandler
{
  public:
    void exec(const std::string& command) override
    {
      if (command.find("INTERSECTION") != 0) {
        CommandHandler::exec(command);
        return;
      }

      //TODO handle INTERSECTION
        std::cout << "handle intersection\n";
    }
};

class SymmetricDifferenceHandler : public CommandHandler
{
  public:
    void exec(const std::string& command) override
    {
      if (command.find("SYMMETRIC_DIFFERENCE") != 0) {
        CommandHandler::exec(command);
        return;
      }

      //TODO handle SYMMETRIC_DIFFERENCE
        std::cout << "handle symmetric difference\n";
    }
};

class UnknownCommandHandler : public CommandHandler
{
  public:
    void exec(const std::string&) override
    {
      //TODO handle unknown command
        std::cout << "error: unknown command\n";
    }
};

}
