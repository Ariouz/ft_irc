/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 08:03:46 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/24 17:45:14 by laguigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

void	user(Server& server, int client_fd, const std::vector<std::string>& args)
{
    Client* client = server.getClient(client_fd);

    if (args.size() == 1 || client == NULL)
    {
        return ;
    }

    if (client->isAuthenticated())
    {
        client->setSendBuffer(Message::ERR_ALREADYREGISTERED(client->getUsername()));
        sendBuffer(*client);
        return ;
    }

    client->setUsername(args[1]);

    if(!client->isAuthenticated())
    {
        if (client->getAuthStatus() != AUTH_USER)
            client->setAuthStatus(AUTH_ERR);
        
        bool authResponse = client->checkAuth();
        std::cout << "check auth: " << authResponse << std::endl;
        if (authResponse == false)
        {
            client->setSendBuffer(Message::ERR_SASLFAIL( client->getUsername() ));
            sendBuffer(*client);
            std::cout << "Auth ended error" << std::endl;
            server.clearClient(client->getFd());
            return ;
        }

        std::cout << "Auth ended success" << std::endl;
        
        client->setAuthStatus(AUTH_OK);
        client->setSendBuffer(Message::RPL_WELCOME(*client));
        sendBuffer(*client);
        client->setSendBuffer(Message::RPL_YOURHOST(client->getUsername()));
        sendBuffer(*client);
        client->setSendBuffer(Message::RPL_CREATE(client->getUsername(), server.getTime()));
        sendBuffer(*client);
    }
}