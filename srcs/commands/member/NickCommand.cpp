#include "commands/member/NickCommand.hpp"

NickCommand::NickCommand(const std::string& name) 
{
    this->_name = name;
}

NickCommand::~NickCommand() {}

void NickCommand::execute(const std::vector<std::string> args, Channel* channel, Client* client, Server& server)
{
    (void) server;
    (void) channel;
    if (args.size() == 0) return ;

    if (client->getAuthStatus() == AUTH_NICK)
        client->setAuthStatus(AUTH_USER);
    else if (!client->isAuthenticated())
    {
        client->setAuthStatus(AUTH_ERR);
        return ;
    }
    client->setNickname(args[0]);
}