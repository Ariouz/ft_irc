#include "Channel.hpp"

# include "ChannelSettings.hpp"

Channel::Channel(Server& server) 
{
    int id = 0;
    while (server.getChannel(id) != NULL)
        id++;
    this->_id = id;
    //this->_settings = ChannelSettings();
}

Channel::~Channel() 
{
}

int Channel::getId() const
{
    return this->_id;
}

/*ChannelSettings* Channel::getSettings(void)
{
    return &this->_settings;
}*/

void Channel::addClient(const Client& client)
{
    this->_clients.push_back(client);
}

void Channel::removeClient(int clientFd)
{
    for (std::size_t index = 0; index < this->_clients.size(); index++)
    {
        if (this->_clients[index].getFd() == clientFd)
        {
            this->_clients.erase(this->_clients.begin() + index);
            break ;
        }
    }
}

void Channel::addOperator(const Client& ope)
{
    this->_operators.push_back(ope);
}

void Channel::removeOperator(int operatorFd)
{
    for (std::size_t index = 0; index < this->_operators.size(); index++)
    {
        if (this->_operators[index].getFd() == operatorFd)
        {
            this->_operators.erase(this->_operators.begin() + index);
            break ;
        }
    }
}

bool Channel::isOperator(int clientFd) const
{
    for (std::size_t index = 0; index < this->_operators.size(); index++)
    {
        if (this->_operators[index].getFd() == clientFd)
            return true;
    }
    return false;
}