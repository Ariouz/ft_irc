#include "commands/operator/InviteCommand.hpp"
#include "ChannelSettings.hpp"

InviteCommand::InviteCommand(const std::string& name) 
{
    this->_name = name;
}

InviteCommand::~InviteCommand() {}

void InviteCommand::execute(const std::vector<std::string> args, Channel* chan, Client* client, Server& server)
{
    (void) server;
    (void) chan;
    if (args.size() != 2)
    {
        client->setSendBuffer(Message::ERR_NEEDMOREPARAMS(client->getUsername(), "INVITE"));
        sendBuffer(*client);
        return ;
    }

    Client *target = server.getClientByNickname(args[0]);
    if (!target)
    {
        client->setSendBuffer(Message::ERR_NOSUCHNICK(client->getUsername(), args[0]));
        sendBuffer(*client);
        return ;
    }

    Channel* channel = server.getChannelByName(args[1]);
    if (!channel)
    {
        client->setSendBuffer(Message::ERR_NOSUCHCHANNEL(client->getUsername(), args[1]));
        sendBuffer(*client);
        return ;
    }

    if (!channel->isClient(client->getFd()))
    {
        client->setSendBuffer(Message::ERR_NOTONCHANNEL(client->getUsername(), channel->getName()));
        sendBuffer(*client);
        return ;
    }

    if (channel->getSettings()->isInviteOnly() && !channel->isOperator(client->getFd()))
    {
        client->setSendBuffer(Message::ERR_CHANOPRIVSNEEDED(client->getUsername(), channel->getName()));
        sendBuffer(*client);
        return ;
    }

    if (channel->isClient(target->getFd()))
    {
        client->setSendBuffer(Message::ERR_USERONCHANNEL(client->getUsername(), target->getNickname(), channel->getName()));
        sendBuffer(*client);
        return ;
    }

    client->setSendBuffer(Message::RPL_INVITING(client->getNickname(), target->getNickname(), channel->getName()));
    sendBuffer(*client);
    target->setSendBuffer(":" + client->getNickname() + " INVITE " + target->getNickname() + " " + channel->getName() + "\r\n");
    sendBuffer(*target);

    if (channel->getSettings()->isInviteOnly())
        channel->addWhitelisted(target);
}