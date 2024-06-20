#include "commands/operator/KickCommand.hpp"

KickCommand::KickCommand(const std::string& name) 
{
    this->_name = name;
}

KickCommand::~KickCommand() {}

void KickCommand::execute(const std::vector<std::string> args, Channel* chan, Client* client, Server& server)
{
    (void) server;
    (void) chan;
    if (args.size() < 2)
    {
        client->setSendBuffer(Message::ERR_NEEDMOREPARAMS(client->getUsername(), "KICK"));
        sendBuffer(*client);
        return ;
    }

    Channel* channel = server.getChannelByName(args[0]);
    if (!channel)
    {
        client->setSendBuffer(Message::ERR_NOSUCHCHANNEL(client->getUsername(), args[0]));
        sendBuffer(*client);
        return ;
    }

    if (!channel->isClient(client->getFd()))
    {
        client->setSendBuffer(Message::ERR_NOTONCHANNEL(client->getUsername(), channel->getName()));
        sendBuffer(*client);
        return ;
    }

    if (!channel->isOperator(client->getFd()))
    {
        client->setSendBuffer(Message::ERR_CHANOPRIVSNEEDED(client->getUsername(), channel->getName()));
        sendBuffer(*client);
        return ;
    }

    Client *target = server.getClientByNickname(args[1]);
    if (!target)
    {
        client->setSendBuffer(Message::ERR_NOSUCHNICK(client->getUsername(), args[1]));
        sendBuffer(*client);
        return ;
    }

    if (!channel->isClient(target->getFd()))
    {
        client->setSendBuffer(Message::ERR_USERNOTINCHANNEL(client->getUsername(), target->getNickname(), channel->getName()));
        sendBuffer(*client);
        return ;
    }

    std::string reason;
    if (args.size() > 2)
    {
            std::vector<std::string> reasonVec (args.begin() + 2, args.end());
            reason = vectorToString(reasonVec);
    } else reason = "An operator kicked you from channel";

    for (std::size_t index = 0; index < channel->getClients().size(); index++)
    {
        Client *chanTarget = channel->getClients()[index];
        chanTarget->setSendBuffer(":"+client->getNickname() + " KICK " + channel->getName() + " " + target->getNickname() + " " + reason + "\r\n");
        sendBuffer(*chanTarget);
    }

    channel->removeClient(target->getFd());
}