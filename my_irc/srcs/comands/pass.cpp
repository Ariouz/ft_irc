/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 08:03:39 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/23 22:04:31 by laguigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

void	pass(Server& server, int client_fd, const std::vector<std::string>& args)
{
    Client* client = server.getClient(client_fd);

    if (client == NULL)
        return ;

    if (args.size() < 2)
    {
        client->setSendBuffer(Message::ERR_NEEDMOREPARAMS(client->getUsername(), args[0]));
        sendBuffer(*client);
        return ;
    }

    if (args[1] == server.getPassword())
    {
        if (client->isAuthenticated())
        {
            client->setSendBuffer(Message::ERR_ALREADYREGISTERED(client->getUsername()));
            sendBuffer(*client);
            return ;
        }
        if (client->getAuthStatus() != AUTH_PASS)
        {
            client->setAuthStatus(AUTH_ERR);
            return ;
        }
        client->setAuthStatus(AUTH_NICK);
        return ;
    }

    else // if wrong pass
    {
        client->setSendBuffer(Message::ERR_PASSWDMISMATCH(client->getUsername()));
        sendBuffer(*client);    
    }
}