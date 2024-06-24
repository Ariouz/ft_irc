/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:07:31 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/24 19:02:02 by laguigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

void part(Server& server, int client_fd, const std::vector<std::string>& args)
{
	Client*	client = server.getClient(client_fd);

    if (args.size() == 1)
    {
        client->setSendBuffer(Message::ERR_NEEDMOREPARAMS(client->getUsername(), "PART"));
        sendBuffer(*client);
        return ;
    }

    std::string channelName = args[1];
    std::string reason = "";
	
    if (args.size() > 2)
    {
        std::vector<std::string> resVec (args.begin() + 2, args.end());
        reason = vectorToString(resVec);
    }

    Channel *channel = server.getChannelByName(channelName);
	
    if (!channel)
    {
        client->setSendBuffer(Message::ERR_NOSUCHCHANNEL(client->getUsername(), channelName));
        sendBuffer(*client);
        return ;
    }

    if (!channel->isClient(client->getUsername()))
    {
        client->setSendBuffer(Message::ERR_NOTONCHANNEL(client->getUsername(), channelName));
        sendBuffer(*client);
        return ;
    }

    for (std::size_t index = 0; index < channel->getClientVector().size(); index++)
    {
        Client *target = channel->getClientVector()[index];
        target->setSendBuffer(":" + client->getNickname() + " PART " + channelName + (reason.empty() ? "" : " :" + reason) + "\r\n");
        sendBuffer(*target);
    }

    channel->removeClient(client->getUsername());

    if (channel->getClientVector().size() == 0)
        server.deleteChannel(channel->getName());
}