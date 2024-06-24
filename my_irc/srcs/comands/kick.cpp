/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:36:12 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/24 17:43:04 by laguigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

void kick(Server& server, int client_fd, const std::vector<std::string>& args)
{
	Client*	client = server.getClient(client_fd);

    if (args.size() < 3)
    {
        client->setSendBuffer(Message::ERR_NEEDMOREPARAMS(client->getUsername(), "KICK"));
        sendBuffer(*client);
        return ;
    }

    Channel* channel = server.getChannelByName(args[1]);
	
    if (!channel)
    {
        client->setSendBuffer(Message::ERR_NOSUCHCHANNEL(client->getUsername(), args[1]));
        sendBuffer(*client);
        return ;
    }

    if (!channel->isClient(client->getUsername()))
    {
        client->setSendBuffer(Message::ERR_NOTONCHANNEL(client->getUsername(), channel->getName()));
        sendBuffer(*client);
        return ;
    }

    if (!channel->isOperator(client->getUsername()))
    {
        client->setSendBuffer(Message::ERR_CHANOPRIVSNEEDED(client->getUsername(), channel->getName()));
        sendBuffer(*client);
        return ;
    }

    Client *target = server.getClientByNick(args[2]);
	
    if (!target)
    {
        client->setSendBuffer(Message::ERR_NOSUCHNICK(client->getUsername(), args[2]));
        sendBuffer(*client);
        return ;
    }

    if (!channel->isClient(target->getUsername()))
    {
        client->setSendBuffer(Message::ERR_USERNOTINCHANNEL(client->getUsername(), target->getNickname(), channel->getName()));
        sendBuffer(*client);
        return ;
    }

    std::string reason;
    if (args.size() > 3)
    {
            std::vector<std::string> reasonVec (args.begin() + 3, args.end());
            reason = vectorToString(reasonVec);
    } else reason = "An operator kicked you from channel";

    for (std::size_t index = 0; index < channel->getClientVector().size(); index++)
    {
        Client *chanTarget = channel->getClientVector()[index];
        chanTarget->setSendBuffer(":" + client->getNickname() + " KICK " + channel->getName() + " " + target->getNickname() + " " + reason + "\r\n");
        sendBuffer(*chanTarget);
    }

    channel->removeClient(target->getUsername());
}