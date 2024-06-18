#include "commands/member/QuitCommand.hpp"

QuitCommand::QuitCommand(const std::string& name) 
{
    this->_name = name;
}

QuitCommand::~QuitCommand() {}

void QuitCommand::execute(const std::vector<std::string> args, Channel* channel, Client* client, Server& server)
{
    (void) args;
    (void) server;
    (void) channel;
    client->setSendBuffer("ERROR Client disconnected");
    sendBuffer(*client);
    server.clearClient(client->getFd());
}