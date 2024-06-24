/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:49:05 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/23 12:54:44 by laguigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

void	ping(Server& server, int client_fd, const std::vector<std::string>& args)
{
	Client*	client = server.getClient(client_fd);

	if (args.size() < 2)
	{
		client->setSendBuffer(Message::ERR_NEEDMOREPARAMS(client->getUsername(), "PING"));
        sendBuffer(*client);
        return ;
	}

	pong(server, client_fd, args);
}
