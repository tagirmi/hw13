#pragma once

#include <string>

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
  CommandHandler* m_next;
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
    }
};

class SymmetricDifferenceHandler : CommandHandler
{
  public:
    void exec(const std::string& command) override
    {
      if (command.find("SYMMETRIC_DIFFERENCE") != 0) {
        CommandHandler::exec(command);
        return;
      }

      //TODO handle SYMMETRIC_DIFFERENCE
    }
};

class UnknownCommandHandler : CommandHandler
{
  public:
    void exec(const std::string&) override
    {
      //TODO handle unknown command
    }
};

}
