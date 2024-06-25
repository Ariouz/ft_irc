#include "commands/member/PrivMsgCommand.hpp"
#include "Bot.hpp"

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

        if (!channel->isClient(client->getFd()))
        {
            client->setSendBuffer(Message::ERR_NOTONCHANNEL(client->getUsername(), channel->getName()));
            sendBuffer(*client);
            return ;
        }

        std::vector<std::string> msgVec (args.begin() + 1, args.end());
        std::string message = vectorToString(msgVec);

        for (std::size_t index = 0; index < channel->getClients().size(); index++)
        {
            Client* target = channel->getClients()[index];
            if (target->getFd() == client->getFd()) continue ;
            target->setSendBuffer(":" + client->getNickname() + " PRIVMSG " + channel->getName() + " " + message+ "\r\n");
            sendBuffer(*target);
        }

        Bot bot = Bot();
        bot.checkBotMention(client, channel, message);
    }
    else // Private message
    {
        Client *target = server.getClientByNickname(args[0]);
        if (!target)
        {
            client->setSendBuffer(Message::ERR_NOSUCHNICK(client->getUsername(), args[0]));
            sendBuffer(*client);
            return ;
        }

        std::vector<std::string> msgVec (args.begin() + 1, args.end());
        std::string message = vectorToString(msgVec);
        
        target->setSendBuffer(":" + client->getNickname() + " PRIVMSG " + target->getNickname() + " " + message+ "\r\n");
        sendBuffer(*target);
    }

    
}