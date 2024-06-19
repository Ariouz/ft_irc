#include "commands/member/PrivMsgCommand.hpp"

PrivMsgCommand::PrivMsgCommand(const std::string& name) 
{
    this->_name = name;
}

PrivMsgCommand::~PrivMsgCommand() {}

void PrivMsgCommand::execute(const std::vector<std::string> args, Channel* chan, Client* client, Server& server)
{
    (void) args;
    (void) server;
    (void) chan;
    
    if (args.size() == 0)
    {
        client->setSendBuffer(Message::ERR_NOTEXTTOSEND(client->getUsername()));
        sendBuffer(*client);
        return ;
    }

    if (args[0].at(0) == '#') // Channel message
    {
        Channel *channel = server.getChannelByName(args[0]);
        if (!channel)
        {
            client->setSendBuffer(Message::ERR_NOSUCHCHANNEL(client->getUsername(), args[0]));
            sendBuffer(*client);
            return ;
        }

        std::vector<std::string> msgVec = args;
        msgVec.erase(msgVec.begin());
        std::string message = vectorToString(msgVec);
        for (std::size_t index = 0; index < channel->getClients().size(); index++)
        {
            Client* target = channel->getClients()[index];
            if (target->getFd() == client->getFd()) continue ;
            target->setSendBuffer(":" + client->getUsername() + " PRIVMSG " + channel->getName() + " " + message+ "\r\n");
            sendBuffer(*target);
        }
    }
    else // Private message
    {
        
    }

}