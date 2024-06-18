# include "commands/other/PongCommand.hpp"
# include "commands/CommandManager.hpp"

PongCommand::PongCommand(const std::string& name) 
{
    this->_name = name;
}

PongCommand::~PongCommand() {}

void PongCommand::execute(const std::vector<std::string> args, Channel* channel, Client* client, Server& server)
{
    (void)server;
    (void)channel;
    if (args.size() == 0)
    {
        client->setSendBuffer(Message::ERR_NEEDMOREPARAMS(client->getUsername(), "PONG"));
        sendBuffer(*client);
        return ;
    }
    client->setSendBuffer("PONG " + args[0] + "\r\n");
    sendBuffer(*client);
}