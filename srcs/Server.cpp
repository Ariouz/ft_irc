/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:23:26 by gurousta          #+#    #+#             */
/*   Updated: 2024/06/17 20:16:30 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Server.hpp"
# include "Client.hpp"
# include "commands/CommandManager.hpp"

Server::Server(std::string port, std::string pass)
{
	this->_serverFd = -1;
	this->_port = ft_stoi(port);
	this->_password = pass;
	this->_commandManager = new CommandManager();
	this->_commandManager->registerAll();
}

Server::~Server(void)
{
	this->closeFd();
	delete this->_commandManager;
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
				std::cout << "Accept Data" << std::endl;
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

	std::cout << buffer << std::endl;

	if (data <= 0)
	{
		std::cout << "Client " << fd << " disconnected" << std::endl;
		this->clearClient(fd);
		return ;
	}

	buffer[1023] = '\0';
	
	std::vector<std::string> lines = splitByCr(buffer);
    Client* client = getClient(fd);

    for (std::size_t index = 0; index < lines.size(); ++index) {
        std::cout << "checking command " << lines[index] << "..." << std::endl;
        
        if (this->_commandManager->isCommand(lines[index]) == 1) {
            std::cout << "Is command: yes" << std::endl;
            
            if (client) {
                this->_commandManager->execute(lines[index], client, 0, *this);
            } else {
                std::cerr << "Error: getClient returned null for fd " << fd << std::endl;
            }
        }
    }
	std::cout << client->getSendBuffer() << " ----- " << client->getFd() << std::endl;
}

void	Server::handlePollout(int fd)
{
	Client *client = getClient(fd);
	if( !client){
		//std::cout << "client null for " << fd << std::endl;
		return;
	}
	//std::cout << "Pollout for " << client->getFd() << std::endl;
	if (client->getSendBuffer().empty()){
		//std::cout <<"empty buffer " << std::endl;
		return ;
	}
	int sent  = send(client->getFd(), client->getSendBuffer().c_str(), client->getSendBuffer().size(), 0);
	std::cout << "sent: " << sent << std::endl;
	client->getSendBuffer().clear();
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

bool	Server::checkAuth(Client& client)
{
	if (client.getAuthStatus() == AUTH_ERR) return false;
	if (client.getAuthStatus() != AUTH_OK && client.getAuthStatus() != AUTH_USER) return false;
	return true;
}

void	Server::createChannel(void)
{
	Channel channel = Channel(*this);
	this->_channels.push_back(channel);
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

std::vector<Client> Server::getClients(void) const
{
	return this->_clients;
}

Client* Server::getClient(int clientFd)
{
	for (std::size_t index = 0; index < this->_clients.size(); index++)
	{
		if (this->_clients[index].getFd() == clientFd)
			return &this->_clients[index];
	}
	
	return NULL;
}

std::vector<Channel> Server::getChannels(void) const
{
	return this->_channels;
}

Channel* Server::getChannel(int channelId)
{
	for (std::size_t index = 0; index < this->_channels.size(); index++)
	{
		if (this->_channels[index].getId() == channelId)
			return &this->_channels[index];
	}
	return NULL;
}

CommandManager* Server::getCommandManager(void)
{
	return this->_commandManager;
}