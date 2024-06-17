#include "commands/member/PassCommand.hpp"

PassCommand::PassCommand(const std::string& name) 
{
    this->_name = name;
}

PassCommand::~PassCommand() {}

void PassCommand::execute(const std::vector<std::string> args, Channel* channel, Client* client, Server& server)
{
    (void) server;
    (void) channel;
   if (args.size() == 0) return ;

    if (client->isAuthenticated()) return ;
    if (client->getAuthStatus() != AUTH_PASS
        || args[0].compare(server.getPassword()) != 0){
        client->setAuthStatus(AUTH_ERR);
        std::cout << "Pass is invalid" << std::endl;
        return ;
    }
    std::cout << "Pass is valid" << std::endl;
    client->setAuthStatus(AUTH_NICK);
}