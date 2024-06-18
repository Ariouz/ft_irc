#include "commands/member/UserCommand.hpp"

UserCommand::UserCommand(const std::string& name)
{
    this->_name = name;
}

UserCommand::~UserCommand() {}

void UserCommand::execute(const std::vector<std::string> args, Channel* channel, Client* client, Server& server)
{
    (void) server;
    (void) channel;
    if (args.size() == 0) return ;

    client->setUsername(args[0]);

    if(!client->isAuthenticated())
    {
        if (client->getAuthStatus() != AUTH_USER)
            client->setAuthStatus(AUTH_ERR);
        
        bool authResponse = server.checkAuth(*client);
        std::cout << "check auth: " << authResponse << std::endl;
        if (authResponse == false)
        {
            client->setSendBuffer(Message::ERR_SASLFAIL( client->getUsername() ));
            sendBuffer(*client);
            std::cout << "Auth ended error" << std::endl;
            server.clearClient(client->getFd());
            return ;
        }

        std::cout << "Auth ended success" << std::endl;
        client->setAuthStatus(AUTH_OK);
        client->setSendBuffer(Message::RPL_WELCOME(*client));
        sendBuffer(*client);
    }
}