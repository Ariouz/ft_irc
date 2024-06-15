/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:23:26 by gurousta          #+#    #+#             */
/*   Updated: 2024/06/15 23:26:43 by laguigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

Server::Server(std::string port, std::string pass)
{
	this->_serverFd = -1;
	this->_port = ft_stoi(port);
	this->_password = pass;
}

Server::~Server(void)
{
	this->closeFd();
}

void	Server::serverInit(void)
{
	sockaddr_in		addr;
	struct pollfd	poll_fd;
	int				opt = 1;


	addr.sin_family = AF_INET;
	addr.sin_port = htons(this->getPort());
	addr.sin_addr.s_addr = INADDR_ANY;

	if ((this->_serverFd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		throw std::runtime_error("Error: failed to create socket...");
	}
	std::cout << "Socket server have been created" << std::endl;

	if (setsockopt(this->getServerFd(), SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
	{
		throw std::runtime_error("Error: failed to set option SO_REUSEADDR to socket");
	}
	std::cout << "Socket server option set to SO_REUSEADDR" << std::endl;

	if (fcntl(this->getServerFd(), F_SETFL, O_NONBLOCK) == -1)
	{
		throw std::runtime_error("Error: failed to set option O_NONBLOCK to socket");
	}
	std::cout << "Socket server set to NONBLOCK" << std::endl;

	if (bind(this->getServerFd(), (struct sockaddr *)&addr, sizeof(addr)) == -1)
	{
		throw std::runtime_error("Error: failed to bind socket");
	}
	std::cout << "Socket server set to pasive mode" << std::endl;

	if (listen(this->getServerFd(), SOMAXCONN) == -1)
	{
		throw std::runtime_error("Error: failed to listen to socket");
	}
	std::cout << "Socket server is now listening up to " << SOMAXCONN << " clients" << std::endl;

	poll_fd.fd= this->getServerFd();
	poll_fd.events = POLLIN;
	poll_fd.revents = 0;

	this->_polls.push_back(poll_fd);

	std::cout << "Waiting to accept connection..." << std::endl;
}

void	Server::loop(void)
{
	if (poll(&this->_polls[0], this->_polls.size(), -1) == -1 && server_signal == false)
	{
		throw std::runtime_error("Error: poll() function failed");
	}

	for (std::size_t index = 0; index < this->_polls.size(); index++)
	{
		if (this->_polls[index].revents & POLLIN)
		{
			if (this->_polls[index].fd == this->getServerFd())
			{
				//std::cout << "Accept Client" << std::endl;
				this->acceptClient();
			}
			else
			{
				//std::cout << "Accept Data" << std::endl;
				this->acceptData(this->_polls[index].fd);
			}
		}

		else if (this->_polls[index].revents & POLLOUT)
		{
			//std::cout << "POLLOUT event" << std::endl; ----> full spam....
			this->handlePollout(this->_polls[index].fd);
		}

		else if (this->_polls[index].revents & POLLERR)
		{
			std::cout << "POLLER event" << std::endl;
			//this->handlePoller();
		}
	}
}

void	Server::acceptClient(void)
{
	Client			client;
	sockaddr_in		client_addr;
	struct pollfd	client_poll_fd;
	int				client_socket_fd;
	socklen_t		client_len;

	client_len = sizeof(client_addr);
	client_socket_fd = accept(this->getServerFd(), (sockaddr *)&client_addr, &client_len);
	if (client_socket_fd == -1)
	{
		throw std::runtime_error("Error: failed to accept client");
	}

	if (fcntl(client_socket_fd, F_SETFL, O_NONBLOCK) == -1)
	{
		throw std::runtime_error("Error: failed to set client to NONBLOCK");
	}

	client.setFd(client_socket_fd);
	client.setIpAddr(inet_ntoa(client_addr.sin_addr));
	this->_clients.push_back(client);
	
	client_poll_fd.fd = client_socket_fd;
	client_poll_fd.events = POLLIN | POLLOUT;
	client_poll_fd.revents = 0;
	this->_polls.push_back(client_poll_fd);

	std::cout << "Client " << client_socket_fd << " connected" << std::endl;
}

void	Server::acceptData(int fd)
{
	char	buffer[1024];
	ssize_t	data;

	std::memset(buffer, 0, sizeof(buffer));

	data = recv(fd, buffer, sizeof(buffer) - 1, 0);

	if (data <= 0)
	{
		std::cout << "Client " << fd << " disconnected" << std::endl;
		this->clearClient(fd);
		return ;
	}

	buffer[1023] = '\0';

	for (std::size_t index = 0; index < this->_clients.size(); index++)
	{
		if (this->_clients[index].getFd() == fd)
		{
			this->_clients[index].setSendBuffer(buffer);
		}
	}
}

void	Server::handlePollout(int fd)
{
	for (std::size_t index = 0; index < this->_clients.size(); index++)
	{
		if (this->_clients[index].getFd() == fd)
		{
			for (std::size_t j = 0; j < this->_clients.size(); j++)
			{
				if (this->_clients[j].getFd() != fd)
				{
					send(this->_clients[j].getFd(), this->_clients[index].getSendBuffer().c_str(), this->_clients[index].getSendBuffer().size() , 0);
				}
			}
			this->_clients[index].getSendBuffer().clear();
		}
	}
}

void	Server::closeFd(void)
{
	for (std::size_t index = 0; index < this->_clients.size(); index++)
	{		
		close(this->_clients[index].getFd());
		std::cout << "Client " << this->_clients[index].getFd() << " have been closed" << std::endl;
	}

	if (this->getServerFd() != -1)
	{
		close(this->getServerFd());
		std::cout << "Server turned Down!" << std::endl;
	}
}

void	Server::clearClient(int fd)
{
	for (std::size_t index = 0; index < this->_clients.size(); index++)
	{
		if (this->_clients[index].getFd() == fd)
		{
			close(this->_clients[index].getFd());
			this->_clients.erase(this->_clients.begin() + index);
		}
	}

	for (std::size_t index = 0; index < this->_polls.size(); index++)
	{
		if (this->_polls[index].fd == fd)
		{
			this->_polls.erase(this->_polls.begin() + index);
		}
	}
}

void	Server::setPassword(std::string pass)
{
	this->_password = pass;
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

const std::string&	Server::getPassword(void) const
{
	return (this->_password);
}