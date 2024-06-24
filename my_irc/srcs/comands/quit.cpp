/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:06:28 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/24 14:10:36 by laguigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

void	quit(Server& server, int client_fd, const std::vector<std::string>& args)
{
	(void) args;

	Client*	client = server.getClient(client_fd);

	client->setSendBuffer("ERROR Client disconnected");
    sendBuffer(*client);
    server.clearClient(client->getFd());
}