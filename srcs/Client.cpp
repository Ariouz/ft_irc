/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:23:17 by gurousta          #+#    #+#             */
/*   Updated: 2024/06/17 17:11:09 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client() : _authStatus(AUTH_INIT) {}

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

void Client::setAuthStatus(int auth)
{
	this->_authStatus = auth;
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

bool	Client::isAuthenticated(void) const
{
	return this->_authStatus == AUTH_OK;
}

int		Client::getAuthStatus(void) const
{
	return this->_authStatus;
}