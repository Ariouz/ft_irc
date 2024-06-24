/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:49:12 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/23 12:56:35 by laguigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

void	pong(Server& server, int client_fd, const std::vector<std::string>& args)
{
	Client*	client = server.getClient(client_fd);

	if (args.size() < 2)
    {
        client->setSendBuffer(Message::ERR_NEEDMOREPARAMS(client->getUsername(), "PONG"));
        sendBuffer(*client);
        return ;
    }
    client->setSendBuffer("PONG " + args[1] + "\r\n");
    sendBuffer(*client);
}
