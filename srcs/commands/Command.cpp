#include "commands/Command.hpp"

Command::Command() {}

Command::~Command() {}

const std::string& Command::getName(void) const
{
    return this->_name;
}

/*void    Command::execute(const std::vector<std::string> args, Channel* channel, Client& client, Server& server) 
{
    (void) args;
    (void) client;
    (void) server;
    (void) channel;
    std::cout << "basic cmd" << std::endl;
}*/