/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:22:22 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/24 17:47:21 by laguigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include "ft_irc.hpp"

class Client;

class Message
{
    public:
        //Welcolme message
        static std::string& RPL_WELCOME(Client& client);
        static std::string& RPL_YOURHOST(const std::string& username);
        static std::string& RPL_CREATE(const std::string& username, const std::string& time);

        //NICK command error
        static std::string& ERR_NONICKNAMEGIVEN(const std::string& username);
        static std::string& ERR_ERRONEUSNICKNAME(const std::string& username, const std::string& argv);
        static std::string& ERR_NICKNAMEINUSE(const std::string& username, const std::string& argv);
        static std::string& ERR_NOSUCHNICK(const std::string& username, const std::string& nickname);

        //PASS wrong pass
        static std::string& ERR_PASSWDMISMATCH(const std::string& username);

        // Authentification fail
        static std::string& ERR_SASLFAIL(const std::string& username);

        // Pas assez de permissions
        static std::string& ERR_NOPRIVS(const std::string& username, const std::string& privilege);
        static std::string& ERR_CHANOPRIVSNEEDED(const std::string& username, const std::string& channel);

        // Flag de /MODE pas pris en charge
        static std::string& ERR_UMODEUNKNOWNFLAG(const std::string& username);

        // Besoin de plus de parametres (args)
        static std::string& ERR_NEEDMOREPARAMS(const std::string& username, const std::string& cmd);

        // Channel Message
        static std::string& ERR_NOSUCHCHANNEL(const std::string& username, const std::string& channel);
        static std::string& ERR_NOTONCHANNEL(const std::string& username, const std::string& channel);
        static std::string& ERR_INVITEONLYCHAN(const std::string& username, const std::string& channel);
        static std::string& ERR_BADCHANNELKEY(const std::string& username, const std::string& channel);
        static std::string& ERR_ALREADYREGISTERED(const std::string& username);
        static std::string& ERR_USERNOTINCHANNEL(const std::string& username, const std::string& nickname, const std::string& channel);
        static std::string& ERR_USERONCHANNEL(const std::string& username, const std::string& nickname, const std::string& channel);
        static std::string& RPL_INVITING(const std::string& username, const std::string& nickname, const std::string& channel);
        static std::string& RPL_NOTOPIC(const std::string& username, const std::string& channel_name);
        static std::string& RPL_TOPIC(const std::string& username, const std::string& channel_name, const std::string& topic);

        // Liste des noms pour JOIN et NAMEs
        static std::string& RPL_NAMREPLY(const std::string& username, const std::string& nickname ,const std::string& channel_name, const std::string& prefix);
        static std::string& RPL_ENDOFNAMES(const std::string& username, const std::string& channel_name);

        static std::string& ERR_NOTEXTTOSEND(const std::string& username);
        
};

#endif