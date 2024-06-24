/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 07:52:13 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/24 18:49:15 by laguigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

static bool    correct_nickname(std::string nickname)
{
    if (nickname[0] == ':' || nickname[0] == '#' || nickname[0] == '&' || nickname.find(" ") != std::string::npos)
    {
        return (false);
    }

    return (true);
}

static bool     not_used_nick(Server& server, std::string nickname)
{
    for (std::size_t index = 0; index < server.getClientsVector().size(); index++)
    {
        if (nickname == server.getClientsVector()[index].getNickname())
        {
            return (false);
        }
    }

    return (true);
}

void	nick(Server& server, int client_fd, const std::vector<std::string>& args)
{
    Client* client = server.getClient(client_fd);

    if (client == NULL)
        return ;

    if ((client->getAuthStatus() == AUTH_OK || client->getAuthStatus() == AUTH_NICK) && (args.size() == 1 || args[1].empty()))
    {
        client->setSendBuffer(Message::ERR_NONICKNAMEGIVEN(client->getUsername()));
        sendBuffer(*client);
        return ;
    }

    if (!correct_nickname(args[1]))
    {
        client->setSendBuffer(Message::ERR_ERRONEUSNICKNAME(client->getUsername(), args[1]));
        sendBuffer(*client);
        return ;
    }

    if (!not_used_nick(server, args[1]))
    {
        client->setSendBuffer(Message::ERR_NICKNAMEINUSE(client->getUsername(), args[1]));
        sendBuffer(*client);
        return ;
    }

    if (client->getAuthStatus() == AUTH_NICK)
        client->setAuthStatus(AUTH_USER);
    else if (!client->isAuthenticated())
    {
        client->setAuthStatus(AUTH_ERR);
        return ;
    }
    if (client->isAuthenticated())
    {
        Client target;
        
        for (std::size_t index = 0; index < server.getClientsVector().size(); index++)
        {
            target = server.getClientsVector()[index];
            target.setSendBuffer(":" + client->getNickname() + " NICK " + args[1] + "\r\n");
            sendBuffer(target);
        }
    }

    client->setNickname(args[1]);
}