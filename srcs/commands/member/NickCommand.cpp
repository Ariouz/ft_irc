#include "commands/member/NickCommand.hpp"

NickCommand::NickCommand(const std::string& name) 
{
    this->_name = name;
}

NickCommand::~NickCommand() {}

static bool    correct_nickname(std::string nickname)
{
    if (nickname[0] == ':' || nickname[0] == '#' || nickname[0] == '&' || nickname.find(" ") != std::string::npos)
    {
        return (false);
    }

    return (true);
}

static bool     not_used_nick(Server& server, std::string nickname)
{
    for (std::size_t index = 0; index < server.getClients().size(); index++)
    {
        if (nickname == server.getClients()[index].getNickname())
        {
            return (false);
        }
    }

    return (true);
}

void NickCommand::execute(const std::vector<std::string> args, Channel* channel, Client* client, Server& server)
{
    (void) server;
    (void) channel;

    if ((client->getAuthStatus() == AUTH_OK || client->getAuthStatus() == AUTH_NICK) && (args.size() == 0 || args[0].empty()))
    {
        client->setSendBuffer(Message::ERR_NONICKNAMEGIVEN(client->getUsername()));
        sendBuffer(*client);
        return ;
    }

    if (!correct_nickname(args[0]))
    {
        client->setSendBuffer(Message::ERR_ERRONEUSNICKNAME(client->getUsername(), args[0]));
        sendBuffer(*client);
        return ;
    }

    if (!not_used_nick(server, args[0]))
    {
        client->setSendBuffer(Message::ERR_NICKNAMEINUSE(client->getUsername(), args[0]));
        sendBuffer(*client);
        return ;
    }

    if (client->getAuthStatus() == AUTH_NICK)
        client->setAuthStatus(AUTH_USER);
    else if (!client->isAuthenticated())
    {
        client->setAuthStatus(AUTH_ERR);
        return ;
    }
    if (client->isAuthenticated())
    {
        Client* target;
        for (std::size_t index = 0; index < server.getClients().size(); index++)
        {
            target = &server.getClients()[index];
            target->setSendBuffer(client->getNickname() + " NICK " + args[0] + "\r\n");
            sendBuffer(*target);
        }
        return ;
    }

    client->setNickname(args[0]);
}