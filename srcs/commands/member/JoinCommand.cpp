#include "commands/member/JoinCommand.hpp"
# include "ChannelSettings.hpp"
# include "Client.hpp"

JoinCommand::JoinCommand(const std::string& name) 
{
    this->_name = name;
}

JoinCommand::~JoinCommand() {}

void JoinCommand::execute(const std::vector<std::string> args, Channel* chan, Client* client, Server& server)
{
    (void) chan;
    if (!client->isAuthenticated())
    {
        client->setSendBuffer(Message::ERR_SASLFAIL(client->getUsername()));
        sendBuffer(*client);
        return ;
    }

    if (args.size() < 1)
    {
        client->setSendBuffer(Message::ERR_NEEDMOREPARAMS(client->getUsername(), "JOIN"));
        sendBuffer(*client);
        return ;
    }

    Channel* channel = server.getChannelByName(args[0]);
    if (!channel)
    {
        server.createChannel(args[0]);
        channel = server.getChannelByName(args[0]);
        channel->addOperator(client);
        std::cout << "Created channel " + args[0] << std::endl;
    }

    if (channel->getSettings()->isInviteOnly() && !channel->isWhitelisted(client->getFd()))
    {
        client->setSendBuffer(Message::ERR_INVITEONLYCHAN(client->getUsername(), args[0]));
        sendBuffer(*client);
        return ;
    }

    if (!channel->getSettings()->getChannelPassword().empty())
    {
        if (args.size() < 2)
        {
            client->setSendBuffer(Message::ERR_NEEDMOREPARAMS(client->getUsername(), "JOIN"));
            sendBuffer(*client);    
            return ;
        }

        if (channel->getSettings()->getChannelPassword().compare(args[1]) != 0)
        {
            client->setSendBuffer(Message::ERR_BADCHANNELKEY(client->getUsername(), args[0]));
            sendBuffer(*client);    
            return ;
        }
    }

    if (channel->isClient(client->getFd()))
        return ;

    channel->addClient(client);
    client->setSendBuffer(":"+client->getNickname() + " JOIN " + channel->getName() + "\r\n");
    sendBuffer(*client);

    for (std::size_t index = 0; index < channel->getClients().size(); index++)
    {
        Client *target = channel->getClients()[index];
        if (target->getFd() == client->getFd()) continue ;
        target->setSendBuffer(":"+client->getNickname() + " JOIN :" + channel->getName() + "\r\n");
        sendBuffer(*target);
    }

    if (!channel->getSettings()->getTopic().empty())
    {
        client->setSendBuffer(Message::RPL_TOPIC(client->getUsername(), channel->getName(), channel->getSettings()->getTopic()));
        sendBuffer(*client);
    }

    for (std::size_t index = 0; index < channel->getClients().size(); index++)
    {
        client->setSendBuffer(Message::RPL_NAMREPLY(channel->getClients()[index], channel));
        sendBuffer(*client);
    }

    client->setSendBuffer(Message::RPL_ENDOFNAMES(*client, *channel));
    sendBuffer(*client);
    
}