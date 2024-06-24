/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:09:38 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/24 17:41:55 by laguigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

void	invite(Server& server, int client_fd, const std::vector<std::string>& args)
{
	Client*	client = server.getClient(client_fd);

    if (args.size() != 3)
    {
        client->setSendBuffer(Message::ERR_NEEDMOREPARAMS(client->getUsername(), "INVITE"));
        sendBuffer(*client);
        return ;
    }

    Client *target = server.getClientByNick(args[1]);
    
    if (!target)
    {
        client->setSendBuffer(Message::ERR_NOSUCHNICK(client->getUsername(), args[1]));
        sendBuffer(*client);
        return ;
    }

    Channel* channel = server.getChannelByName(args[2]);
    
    if (!channel)
    {
        client->setSendBuffer(Message::ERR_NOSUCHCHANNEL(client->getUsername(), args[2]));
        sendBuffer(*client);
        return ;
    }

    if (!channel->isClient(client->getUsername()))
    {
        client->setSendBuffer(Message::ERR_NOTONCHANNEL(client->getUsername(), channel->getName()));
        sendBuffer(*client);
        return ;
    }

    if (channel->getMode().find("i") != std::string::npos && !channel->isOperator(client->getUsername()))
    {
        client->setSendBuffer(Message::ERR_CHANOPRIVSNEEDED(client->getUsername(), channel->getName()));
        sendBuffer(*client);
        return ;
    }

    if (channel->isClient(target->getUsername()))
    {
        client->setSendBuffer(Message::ERR_USERONCHANNEL(client->getUsername(), target->getNickname(), channel->getName()));
        sendBuffer(*client);
        return ;
    }

    client->setSendBuffer(Message::RPL_INVITING(client->getNickname(), target->getNickname(), channel->getName()));
    sendBuffer(*client);
    target->setSendBuffer(":" + client->getNickname() + " INVITE " + target->getNickname() + " " + channel->getName() + "\r\n");
    sendBuffer(*target);

    if (channel->getMode().find("i") != std::string::npos)
		channel->getWhitelistVector().push_back(target->getUsername());
}