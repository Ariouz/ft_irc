/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:46:29 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/24 14:03:40 by laguigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Client.hpp"
#include "../../includes/Server.hpp"

Client::Client() : _authStatus(AUTH_INIT) {}

Client::~Client() {}

void	Client::leaveAll(Server& server)
{
	for (std::size_t index = 0; index < server.getChannelVector().size(); index++)
	{
		server.getChannelVector()[index].removeClient(this->getUsername());
		server.getChannelVector()[index].removeOperator(this->getUsername());
		server.getChannelVector()[index].removeWhitelist(this->getUsername());
		if (server.getChannelVector()[index].getClientVector().size() == 0)
		{
			server.getChannelVector().erase(server.getChannelVector().begin() + index);
			index = index - 1;
		}
	}
}

bool	Client::isAuthenticated() const
{
	return (this->_authStatus == AUTH_OK);
}

bool	Client::checkAuth(void) const
{
	if (this->getAuthStatus() == AUTH_ERR) return false;
	if (this->getAuthStatus() != AUTH_OK && this->getAuthStatus() != AUTH_USER) return false;
	return true;
}


//SETTER
void	Client::setFd(int fd) 						{this->_fd = fd;};
void	Client::setUsername(std::string username)	{this->_username = username;};
void	Client::setNickname(std::string nickname)	{this->_nickname = nickname;};
void	Client::setIpAddr(std::string ipAddr)		{this->_ipAddr = ipAddr;};
void	Client::setSendBuffer(std::string buffer)	{this->_sendBuffer = buffer;};
void	Client::setReadBuffer(std::string buffer)	{this->_readBuffer += buffer;};
void	Client::setAuthStatus(int auth)				{this->_authStatus = auth;};

//GETTER
int				Client::getFd(void) const			{return this->_fd;};
int				Client::getAuthStatus(void) const	{return this->_authStatus;};
std::string&	Client::getUsername(void)			{return this->_username;};
std::string&	Client::getNickname(void)			{return this->_nickname;};
std::string&	Client::getIpAddr(void)				{return this->_ipAddr;};
std::string&	Client::getSendBuffer(void)			{return this->_sendBuffer;};
std::string&	Client::getReadBuffer(void)			{return this->_readBuffer;};
