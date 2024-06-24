/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 08:18:00 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/24 17:47:41 by laguigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

std::string& Message::RPL_WELCOME(Client& client) 
{
    static std::string res;
    res = "001 " + client.getUsername() + " :Welcome to the ft_irc Network, " + client.getNickname() + "\r\n";
    return res;
}

std::string& Message::RPL_YOURHOST(const std::string& username)
{
    static std::string  res;
    res = "002 " + username + " :Your host is gurousta/vicalvez, running version 1.0\r\n";
    return res;
}

std::string& Message::RPL_CREATE(const std::string& username, const std::string& time)
{
    static std::string  res;
    res = "003 " + username + " :This server was created " + time + "\r\n";
    return res;
}

std::string& Message::RPL_NAMREPLY(const std::string& username, const std::string& nickname ,const std::string& channel_name, const std::string& prefix)
{
    static std::string res;
    res = "353 " + username + " = " + channel_name + " :" + prefix + nickname + "\r\n";
    return res;
}

std::string& Message::ERR_SASLFAIL(const std::string& username) 
{
    static std::string res;
    res = "904 " + username + " :SASL authentication failed\r\n";
    return res;
}

std::string& Message::ERR_NOPRIVS(const std::string& username, const std::string& privilege) 
{
    static std::string res;
    res = "723 "  + username + " " + privilege + " :Insufficient oper privileges.\r\n";
    return res;
}

std::string& Message::ERR_UMODEUNKNOWNFLAG(const std::string& username) 
{
    static std::string res;
    res = "501 "  + username + " :Unknown MODE flag\r\n";
    return res;
}

std::string& Message::ERR_NEEDMOREPARAMS(const std::string& username, const std::string& cmd) 
{
    static std::string res;
    res = "461 " + username + " "+cmd+" :Not enough parameters\r\n";
    return res;
}

std::string& Message::ERR_NOSUCHCHANNEL(const std::string& username, const std::string& channel)
{
    static std::string res;
    res = "403 " + username + " " + channel + " :No such channel\r\n";
    return res;
}

std::string& Message::ERR_NOSUCHNICK(const std::string& username, const std::string& nickname)
{
    static std::string res;
    res = "401 " + username +  " " + nickname + " :No such nick/channel\r\n";
    return res;
}

std::string& Message::ERR_USERNOTINCHANNEL(const std::string& username, const std::string& nickname, const std::string& channel)
{
    static std::string res;
    res = "441 " + username + " " + nickname + " " + channel + " :They aren't on that channel\r\n";
    return res;
}

std::string& Message::RPL_INVITING(const std::string& username, const std::string& nickname, const std::string& channel)
{
    static std::string res;
    res = "341 "+ username+ " " + nickname + " " + channel + "\r\n";
    return res;
}

std::string& Message::RPL_NOTOPIC(const std::string& username, const std::string& channel_name)
{
    static std::string res;
    res = "331 " +  username + " " + channel_name + " :No topic is set\r\n";
    return res;
}

std::string& Message::RPL_TOPIC(const std::string& username, const std::string& channel_name, const std::string& topic)
{
    static std::string res;
    res = "332 " + username + " " + channel_name + " :" + topic + "\r\n";
    return res;
}

std::string& Message::ERR_USERONCHANNEL(const std::string& username, const std::string& nickname, const std::string& channel)
{
    static std::string res;
    res = "443 " + username + " " + nickname + " " + channel + " :is already on channel\r\n";
    return res;
}

std::string& Message::ERR_INVITEONLYCHAN(const std::string& username, const std::string& channel)
{
    static std::string res;
    res = "473 " + username + " " + channel + " :Cannot join channel (+i)\r\n";
    return res;
}

std::string& Message::ERR_BADCHANNELKEY(const std::string& username, const std::string& channel)
{
    static std::string res;
    res = "475 "+username+ " " + channel + " :Cannot join channel (+k)\r\n";
    return res;
}

std::string& Message::ERR_NOTONCHANNEL(const std::string& username, const std::string& channel)
{
    static std::string res;
    res = "442 "+ username + " " + channel + " :You're not on that channel\r\n";
    return res;
}

std::string& Message::ERR_CHANOPRIVSNEEDED(const std::string& username, const std::string& channel)
{
    static std::string res;
    res = "482 "+ username + " " + channel + " :You're not channel operator\r\n";
    return res;
}

std::string& Message::RPL_ENDOFNAMES(const std::string& username, const std::string& channel_name)
{
    static std::string res;
    res = "366 "+ username + " " + channel_name + " :End of /NAMES list\r\n";
    return res;
}

std::string& Message::ERR_ALREADYREGISTERED(const std::string& username)
{
    static std::string res;
    res = "462 "  + username + " :You may not reregister\r\n";
    return res;
}

std::string& Message::ERR_NONICKNAMEGIVEN(const std::string& username)
{
    static std::string  res;
    res = "431 " + username + " :No nickname given\r\n";
    return (res);
}

std::string& Message::ERR_ERRONEUSNICKNAME(const std::string& username, const std::string& argv)
{
    static std::string res;
    res = "432 " + username + " " + argv + " :Erroneus nickname\r\n";
    return res;
}

std::string& Message::ERR_NICKNAMEINUSE(const std::string& username, const std::string& argv)
{
    static std::string res;
    res = "433 " + username + " " + argv + " :Nickname is already in use\r\n";
    return (res);
}

std::string& Message::ERR_NOTEXTTOSEND(const std::string& username)
{
    static std::string res;
    res = "412 " + username + " :No text to send\r\n";
    return (res);
}

std::string& Message::ERR_PASSWDMISMATCH(const std::string& username)
{
    static std::string  res;
    res = "464 " + username + " :Password incorrect\r\n";
    return res;
}
