#include "commands/other/PingCommand.hpp"
# include "commands/CommandManager.hpp"

PingCommand::PingCommand(const std::string& name) 
{
    this->_name = name;
}

PingCommand::~PingCommand() {}

void PingCommand::execute(const std::vector<std::string> args, Channel* channel, Client* client, Server& server)
{
    if (args.size() == 0)
    {
        client->setSendBuffer(Message::ERR_NEEDMOREPARAMS(client->getUsername(), "PING"));
        sendBuffer(*client);
        return ;
    }
    Command* cmd = server.getCommandManager().getCommand("PONG");
    cmd->execute(args, channel, client, server);
}