/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurousta <gurousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:23:26 by gurousta          #+#    #+#             */
/*   Updated: 2024/06/14 20:16:47 by gurousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

Server::Server()
{
	//Server::_serverSignal = false;
	this->_serverFd = -1;
	this->_port = 4242;
}

Server::~Server()
{
	this->closeFd();
}

/*void	Server::signalHandler(int signum)
{
	(void) signum;
	Server::_serverSignal = true;
}*/

void	Server::serverInit()
{
	t_socketaddr	add;
	t_poll_fd		poll;
	int				opt = 1;

	add.family = AF_INET;
	add.port = htons(this->getPort());
	add.addr.addr = INADDR_ANY;

	if ((this->_serverFd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		throw std::runtime_error("Error: failed to create socket...");
	}
	
	if (setsockopt(this->getServerFd(), SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
	{
		throw std::runtime_error("Error: failed to set option SO_REUSEADDR to socket");
	}

	if (fcntl(this->getServerFd(), F_SETFL, O_NONBLOCK) == -1)
	{
		throw std::runtime_error("Error: failed to set option O_NONBLOCK to socket");
	}

	/*if (bind(this->getServerFd(), (struct sockaddr *)&add, sizeof(add)) == -1)
	{
		throw std::runtime_error("Error: failed to bind socket");
	}*/

	if (listen(this->getServerFd(), SOMAXCONN) == -1)
	{
		throw std::runtime_error("Error: failed to listen to socket");
	}

	poll.fd= this->getServerFd();
	poll.event = POLLIN;
	poll.revent = 0;

	this->_polls.push_back(poll);

	std::cout << "Waiting to accept connection" << std::endl;
}

void	Server::closeFd()
{
	for (std::size_t index = 0; index < this->_clients.size(); index++)
	{
		close(this->_clients[index].getFd());
	}

	if (this->getServerFd() != -1)
	{
		close(this->getServerFd());
	}
}

void	Server::setPort(int port)
{
	this->_port = port;
}

void	Server::setServerFd(int fd)
{
	this->_serverFd = fd;
}

int		Server::getPort(void) const
{
	return (this->_port);
}

int		Server::getServerFd(void) const
{
	return (this->_serverFd);
}