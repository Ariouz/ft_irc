#include "commands/other/CapCommand.hpp"

CapCommand::CapCommand(const std::string& name) 
{
    this->_name = name;
}

CapCommand::~CapCommand() {}

void CapCommand::execute(const std::vector<std::string> args, Channel* channel, Client* client, Server& server)
{
    (void) server;
    (void) channel;
    //if (args.size() == 0) return ;

    std::cout << "Cap Command execute" << std::endl;
    std::cout << "args[0] : " + args[0] << std::endl;

    if (args[0].compare("LS") == 0)
    {
        if (client->isAuthenticated()) return ;
        std::cout << "Auth started" << std::endl;
        client->setAuthStatus(AUTH_PASS);
    }

    if (args[0].compare("END") == 0)
    {
        bool authResponse = server.checkAuth(*client);
        if (authResponse == false)
        {
            client->setSendBuffer(Message::ERR_SASLFAIL( client->getUsername() ));
            send(client->getFd(), client->getSendBuffer().c_str(), client->getSendBuffer().size(), 0);
            client->getSendBuffer().clear();
            std::cout << "Auth ended error" << std::endl;
            server.clearClient(client->getFd());
            return ;
        }
        std::cout << "Auth ended" << std::endl;
        client->setAuthStatus(AUTH_OK);
        client->setSendBuffer(Message::RPL_WELCOME(*client));
    }
}