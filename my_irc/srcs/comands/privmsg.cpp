/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:34:31 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/24 19:25:36 by laguigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

void	privmsg(Server& server, int client_fd, const std::vector<std::string>& args)
{
	Client*	client = server.getClient(client_fd);

    if (args.size() == 1)
    {
        client->setSendBuffer(Message::ERR_NOTEXTTOSEND(client->getUsername()));
        sendBuffer(*client);
        return ;
    }

    if (args[1].at(0) == '#') // Channel message
    {
        Channel *channel = server.getChannelByName(args[1]);
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

        std::vector<std::string> msgVec (args.begin() + 2, args.end());
        std::string message = vectorToString(msgVec);

        for (std::size_t index = 0; index < channel->getClientVector().size(); index++)
        {
            Client* target = channel->getClientVector()[index];

            if (target->getFd() == client->getFd())
				continue ;
			
            target->setSendBuffer(":" + client->getNickname() + " PRIVMSG " + channel->getName() + " " + message+ "\r\n");
            sendBuffer(*target);
        }
    }
    else // Private message
    {
        Client* target = server.getClientByNick(args[1]);
        
        if (!target)
        {
            client->setSendBuffer(Message::ERR_NOSUCHNICK(client->getUsername(), args[1]));
            sendBuffer(*client);
            return ;
        }

        std::vector<std::string> msgVec (args.begin() + 2, args.end());
        std::string message = vectorToString(msgVec);
        
        target->setSendBuffer(":" + client->getNickname() + " PRIVMSG " + target->getNickname() + " " + message + "\r\n");
        sendBuffer(*target);
    }

}