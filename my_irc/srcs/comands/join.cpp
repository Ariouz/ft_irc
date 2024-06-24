/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:48:32 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/24 17:42:59 by laguigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

void	join(Server& server, int client_fd, const std::vector<std::string>& args)
{
	bool	just_created    = false;
	Client*	client          = server.getClient(client_fd);

    if (!client->isAuthenticated())
    {
        client->setSendBuffer(Message::ERR_SASLFAIL(client->getUsername()));
        sendBuffer(*client);
        return ;
    }

    if (args.size() < 2)
    {
        client->setSendBuffer(Message::ERR_NEEDMOREPARAMS(client->getUsername(), "JOIN"));
        sendBuffer(*client);
        return ;
    }

    Channel* channel = server.getChannelByName(args[1]);

    if (!channel)
    {
    	server.createChannel(args);
        channel = server.getChannelByName(args[1]);
        channel->addOperator(client->getUsername());
		just_created = true;
        std::cout << "Created channel " + args[1] << std::endl;
    }

    if (channel->getMode().find("i") != std::string::npos && !channel->isWhitelisted(client->getUsername()))
    {
        client->setSendBuffer(Message::ERR_INVITEONLYCHAN(client->getUsername(), args[1]));
        sendBuffer(*client);
        return ;
    }

    if (!channel->getPass().empty() && just_created == false)
    {
        if (args.size() < 2)
        {
            client->setSendBuffer(Message::ERR_NEEDMOREPARAMS(client->getUsername(), "JOIN"));
            sendBuffer(*client);    
            return ;
        }

        if (channel->getPass() != args[1])
        {
            client->setSendBuffer(Message::ERR_BADCHANNELKEY(client->getUsername(), args[1]));
            sendBuffer(*client);    
            return ;
        }
    }

    if (channel->isClient(client->getUsername()))
        return ;

    channel->addClient(client);
    client->setSendBuffer(":" + client->getNickname() + " JOIN " + channel->getName() + "\r\n");
    sendBuffer(*client);

    for (std::size_t index = 0; index < channel->getClientVector().size(); index++)
    {
        Client *target = channel->getClientVector()[index];
        if (target->getFd() == client->getFd())
			continue ;
        target->setSendBuffer(":" + client->getNickname() + " JOIN :" + channel->getName() + "\r\n");
        sendBuffer(*target);
    }

    if (!channel->getTopic().empty())
    {
        client->setSendBuffer(Message::RPL_TOPIC(client->getUsername(), channel->getName(), channel->getTopic()));
        sendBuffer(*client);
    }

    for (std::size_t index = 0; index < channel->getClientVector().size(); index++)
    {
		std::string prefix = channel->isOperator(channel->getClientVector()[index]->getUsername()) ? "@" : "";
        client->setSendBuffer(Message::RPL_NAMREPLY(channel->getClientVector()[index]->getUsername(), channel->getClientVector()[index]->getNickname(), channel->getName(), prefix));
        sendBuffer(*client);
    }

    client->setSendBuffer(Message::RPL_ENDOFNAMES(client->getUsername(), channel->getName()));
    sendBuffer(*client);
}