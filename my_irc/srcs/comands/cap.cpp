/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 07:47:55 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/24 17:25:57 by laguigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

void	cap(Server& server, int client_fd, const std::vector<std::string>& args)
{
	Client*	client = server.getClient(client_fd);
    
    if (args.size() < 2 || client == NULL)
    {
        return ;
    }

	if (args[1] == "LS")
	{
		if (client->isAuthenticated())
		{
			return ;
		}
		client->setAuthStatus(AUTH_PASS);
        return ;
	}

	if (args[1] == "END")
    {
        if (client->checkAuth() == false)
        {
            client->setSendBuffer(Message::ERR_SASLFAIL(client->getUsername() ));
            sendBuffer(*client);
            server.clearClient(client->getFd());
            return ;
        }
        client->setAuthStatus(AUTH_OK);
        client->setSendBuffer(Message::RPL_WELCOME(*client));
        sendBuffer(*client);
    }
}