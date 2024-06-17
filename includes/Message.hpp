#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include "ft_irc.hpp"

class Client;

class Message
{
    public:
        static std::string& RPL_WELCOME(const Client& client);
        static std::string& ERR_SASLFAIL(const std::string& username);
        static std::string& ERR_NOPRIVS(const std::string& username, const std::string& privilege);
        static std::string& ERR_UMODEUNKNOWNFLAG(const std::string& username);
};

#endif