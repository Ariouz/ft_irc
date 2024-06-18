# include "Channel.hpp"
# include "ChannelSettings.hpp"

Channel::Channel(Server& server, const std::string& name) : _name(name)
{
    int id = 0;
    while (server.getChannel(id) != NULL)
        id++;
    this->_id = id;
    this->_settings = new ChannelSettings();
}

Channel::~Channel() 
{
    delete this->_settings;
}

int Channel::getId() const
{
    return this->_id;
}

ChannelSettings* Channel::getSettings(void)
{
    return this->_settings;
}

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

void Channel::addWhitelisted(const Client& client)
{
    this->_whitelist.push_back(client);
}

void Channel::removeWhitelisted(int clientFd)
{
    for (std::size_t index = 0; index < this->_whitelist.size(); index++)
    {
        if (this->_whitelist[index].getFd() == clientFd)
        {
            this->_whitelist.erase(this->_whitelist.begin() + index);
            break ;
        }
    }
}

bool Channel::isWhitelisted(int clientFd) const
{
    for (std::size_t index = 0; index < this->_whitelist.size(); index++)
    {
        if (this->_whitelist[index].getFd() == clientFd)
            return true;
    }
    return false;
}

const std::string&  Channel::getName(void) const
{
    return this->_name;
}

std::vector<Client> Channel::getClients(void) 
{
    return this->_clients;
}