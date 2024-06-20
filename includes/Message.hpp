#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include "ft_irc.hpp"

class Client;

class Channel;

class Message
{
    public:
        static std::string& RPL_WELCOME(Client& client);
        static std::string& RPL_TOPIC(const std::string& username, const std::string& channel, const std::string& topic);

        //NICK command error
        static std::string& ERR_NONICKNAMEGIVEN(const std::string& username);
        static std::string& ERR_ERRONEUSNICKNAME(const std::string& username, const std::string& argv);
        static std::string& ERR_NICKNAMEINUSE(const std::string& username, const std::string& argv);
        static std::string& ERR_NOSUCHNICK(const std::string& username, const std::string& nickname);

        // Authentification fail
        static std::string& ERR_SASLFAIL(const std::string& username);
        static std::string& ERR_ALREADYREGISTERED(const std::string& username);

        // Pas assez de permissions
        static std::string& ERR_NOPRIVS(const std::string& username, const std::string& privilege);
        static std::string& ERR_CHANOPRIVSNEEDED(const std::string& username, const std::string& channel);

        // Flag de /MODE pas pris en charge
        static std::string& ERR_UMODEUNKNOWNFLAG(const std::string& username);

        // Besoin de plus de parametres (args)
        static std::string& ERR_NEEDMOREPARAMS(const std::string& username, const std::string& cmd);

        // Messages de channel
        static std::string& ERR_NOSUCHCHANNEL(const std::string& username, const std::string& channel);
        static std::string& ERR_NOTONCHANNEL(const std::string& username, const std::string& channel);
        static std::string& ERR_INVITEONLYCHAN(const std::string& username, const std::string& channel);
        static std::string& ERR_BADCHANNELKEY(const std::string& username, const std::string& channel);
        static std::string& ERR_USERNOTINCHANNEL(const std::string& username, const std::string& nickname, const std::string& channel);
        static std::string& ERR_USERONCHANNEL(const std::string& username, const std::string& nickname, const std::string& channel);
        static std::string& RPL_INVITING(const std::string& username, const std::string& nickname, const std::string& channel);

    
        // Liste des noms pour JOIN et NAMEs
        static std::string& RPL_NAMREPLY(Client* client, const Channel* channel);
        static std::string& RPL_ENDOFNAMES(Client& client, const Channel& channel);

        static std::string& ERR_NOTEXTTOSEND(const std::string& username);
        
};

#endif