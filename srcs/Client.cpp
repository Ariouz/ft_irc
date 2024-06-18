/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:23:17 by gurousta          #+#    #+#             */
/*   Updated: 2024/06/18 17:28:40 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Server.hpp"

Client::Client() : _authStatus(AUTH_INIT) {}

Client::~Client() {}

void	Client::leaveAll(Server& server)
{
	for (std::size_t index = 0; index < server.getChannels().size(); index++)
	{
		server.getChannels()[index]->removeClient(this->getFd());
		server.getChannels()[index]->removeOperator(this->getFd());
		server.getChannels()[index]->removeWhitelisted(this->getFd());
	}
}

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

void Client::setAuthStatus(int auth)
{
	this->_authStatus = auth;
}

int		Client::getFd(void) const
{
	return (this->_fd);
}

std::string&	Client::getUsername(void)
{
	return (this->_username);
}

std::string&	Client::getNickname(void)
{
	return (this->_nickname);
}

std::string&	Client::getIpAddr(void)
{
	return (this->_ipAddr);
}

std::string&	Client::getSendBuffer(void)
{
	return (this->_sendBuffer);
}

bool	Client::isAuthenticated(void) const
{
	return this->_authStatus == AUTH_OK;
}

int		Client::getAuthStatus(void) const
{
	return this->_authStatus;
}