/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:52:42 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/24 20:41:23 by laguigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

void	topic(Server& server, int client_fd, const std::vector<std::string>& args)
{
	Client*	client = server.getClient(client_fd);

	if (args.size() < 2)
	{
		client->setSendBuffer(Message::ERR_NEEDMOREPARAMS(client->getUsername(), args[0]));
		sendBuffer(*client);
		return ;
	}

	Channel*	channel = server.getChannelByName(args[1]);

	if (!channel)
	{
		client->setSendBuffer(Message::ERR_NOSUCHCHANNEL(client->getUsername(), args[1]));
		sendBuffer(*client);
		return ;
	}

	if (!channel->isClient(client->getUsername()))
	{
		client->setSendBuffer(Message::ERR_NOTONCHANNEL(client->getUsername(), args[1]));
		sendBuffer(*client);
		return ;
	}

	if (args.size() == 2)
	{
		if (channel->getTopic().empty() == true)
		{
			client->setSendBuffer(Message::RPL_NOTOPIC(client->getUsername(), channel->getName()));
			sendBuffer(*client);
			return ;
		}
		
		client->setSendBuffer(Message::RPL_TOPIC(client->getUsername(), channel->getName(), channel->getTopic()));
		sendBuffer(*client);
		return ;
	}
	 
	// if args > 2 
	if (channel->getMode().find("t") != std::string::npos && channel->isOperator(client->getUsername()) == false)
	{
		client->setSendBuffer(Message::ERR_CHANOPRIVSNEEDED(client->getUsername(), args[1]));
		sendBuffer(*client);
		return ;
	}

	if (args[2].at(0) == ':' && args[2].size() == 1)
	{
		channel->getTopic().clear();
		return ;
	}

	std::vector<std::string>	msgVec (args.begin() + 2, args.end());
	std::string					topic = vectorToString(msgVec);
	topic.erase(0);

	channel->setTopic(topic);
}