/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_buffer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 08:34:58 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/19 08:35:35 by laguigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

void    sendBuffer(Client& client)
{
	send(client.getFd(), client.getSendBuffer().c_str(), client.getSendBuffer().size(), 0);
    client.getSendBuffer().clear();
}