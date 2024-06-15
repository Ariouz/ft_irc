/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:23:17 by gurousta          #+#    #+#             */
/*   Updated: 2024/06/15 23:05:52 by laguigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Client.hpp"

Client::Client() {}

Client::~Client() {}

void	Client::setFd(int fd)
{
	this->_fd = fd;
}

void	Client::setUsername(std::string username)
{
	this->_username = username;
}

void	Client::setNickname(std::string nickname)
{
	this->_nickname = nickname;
}

void	Client::setIpAddr(std::string ipAddr)
{
	this->_ipAddr = ipAddr;
}

void	Client::setSendBuffer(std::string buffer)
{
	this->_sendBuffer = buffer;
}

int		Client::getFd(void) const
{
	return (this->_fd);
}

const std::string&	Client::getUsername(void) const
{
	return (this->_username);
}

const std::string&	Client::getNickname(void) const
{
	return (this->_nickname);
}

const std::string&	Client::getIpAddr(void) const
{
	return (this->_ipAddr);
}

std::string&	Client::getSendBuffer(void)
{
	return (this->_sendBuffer);
}