#include "commands/operator/ModeCommand.hpp"

ModeCommand::ModeCommand(const std::string& name) 
{
    this->_name = name;
}

ModeCommand::~ModeCommand() {}

void ModeCommand::execute(const std::vector<std::string> args, Channel* channel, Client* client, Server& server)
{
    (void) server;
    (void) channel;
    (void) args;
    //if (args[0].compare("+i") == 0) // temp
    //{
        client->setSendBuffer(Message::ERR_UMODEUNKNOWNFLAG(client->getUsername()));
        send(client->getFd(), client->getSendBuffer().c_str(), client->getSendBuffer().size(), 0);
        client->getSendBuffer().clear();
    //}
}