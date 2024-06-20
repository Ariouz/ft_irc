#include "commands/member/PartCommand.hpp"

PartCommand::PartCommand(const std::string& name) 
{
    this->_name = name;
}

PartCommand::~PartCommand() {}

void PartCommand::execute(const std::vector<std::string> args, Channel* chan, Client* client, Server& server)
{
    (void) args;
    (void) server;
    (void) chan;
    
    if (args.size() == 0)
    {
        client->setSendBuffer(Message::ERR_NEEDMOREPARAMS(client->getUsername(), "PART"));
        sendBuffer(*client);
        return ;
    }

    std::string channelName = args[0];
    std::string reason = "";
    if (args.size() > 1)
    {
        std::vector<std::string> resVec = args;
        resVec.erase(resVec.begin());
        reason = vectorToString(resVec);
    }

    Channel *channel = server.getChannelByName(channelName);
    if (!channel)
    {
        client->setSendBuffer(Message::ERR_NOSUCHCHANNEL(client->getUsername(), channelName));
        sendBuffer(*client);
        return ;
    }

    if (!channel->isClient(client->getFd()))
    {
        client->setSendBuffer(Message::ERR_NOTONCHANNEL(client->getUsername(), channelName));
        sendBuffer(*client);
        return ;
    }

    for (std::size_t index = 0; index < channel->getClients().size(); index++)
    {
        Client *target = channel->getClients()[index];
        target->setSendBuffer(":" + client->getNickname() + " PART " + channelName + (reason.empty() ? "" : " :" + reason) + "\r\n");
        sendBuffer(*target);
    }

    channel->removeClient(client->getFd());

}