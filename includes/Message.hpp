#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include "ft_irc.hpp"

class Client;

class Channel;

class Message
{
    public:
        static std::string& RPL_WELCOME(const Client& client);
        static std::string& RPL_TOPIC(const std::string& username, const std::string& channel, const std::string& topic);

        static std::string& ERR_SASLFAIL(const std::string& username);
        static std::string& ERR_NOPRIVS(const std::string& username, const std::string& privilege);
        static std::string& ERR_UMODEUNKNOWNFLAG(const std::string& username);
        static std::string& ERR_NEEDMOREPARAMS(const std::string& username, const std::string& cmd);
        static std::string& ERR_NOSUCHCHANNEL(const std::string& username, const std::string& channel);
        static std::string& ERR_INVITEONLYCHAN(const std::string& username, const std::string& channel);
        static std::string& ERR_BADCHANNELKEY(const std::string& username, const std::string& channel);
        static std::string& RPL_NAMREPLY(const Client& client, const Channel& channel);
        static std::string& RPL_ENDOFNAMES(const Client& client, const Channel& channel);
};

#endif