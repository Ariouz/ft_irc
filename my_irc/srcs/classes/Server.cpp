/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:28:23 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/24 18:27:28 by laguigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/Server.hpp"
# include "../../includes/Client.hpp"

void	debug(Server& server)
{
	std::cout << "----------------DEBUG-------------------------" << std::endl;
	std::cout << "There is " << server.getClientsVector().size() << " clients in my server" << std::endl;
	
	for (std::size_t index = 0; index < server.getClientsVector().size(); index++)
	{
		if (server.getClientsVector()[index].isAuthenticated() == false)
			continue;
		std::cout << "Client no:	" << index + 1 << std::endl;
		std::cout << "name:			" << server.getClientsVector()[index].getUsername() << std::endl;
		std::cout << "nickname:		" << server.getClientsVector()[index].getNickname() << std::endl << std::endl;
	}

	std::cout << "there is " << server.getChannelVector().size() << " channel in my server" << std::endl;

	for (std::size_t index = 0; index < server.getChannelVector().size(); index++)
	{
		std::cout << "channel name:		" << server.getChannelVector()[index].getName() << std::endl;
		std::cout << "channel mode:		" << server.getChannelVector()[index].getMode() << std::endl;
		std::cout << "channel pass:		" << server.getChannelVector()[index].getPass() << std::endl;
		std::cout << "channel topic:	" << server.getChannelVector()[index].getTopic() << std::endl;

		std::cout << "Let's see all the client from this channel" << std::endl;
		for (std::size_t j = 0; j < server.getChannelVector()[index].getClientVector().size(); j++)
		{
			std::cout << "client name: " << server.getChannelVector()[index].getClientVector()[j]->getUsername() << std::endl;
			std::cout << "client nick: " << server.getChannelVector()[index].getClientVector()[j]->getNickname() << std::endl;
		}
	}
	std::cout << "----------------DEBUG-END---------------------" << std::endl;
}


Server::Server(std::string port, std::string pass)
{
	std::string	all_cmd[] = 
	{
		"CAP",
		"PASS",
		"NICK",
		"USER",
		"PING",
		"PONG",
		"JOIN",
		"INVITE",
		"KICK",
		"PART",
		"PRIVMSG",
		"QUIT",
		"TOPIC"
	};
	
	char				buffer[80];
	std::time_t			now = std::time(NULL);
	struct std::tm*		timeinfo = std::localtime(&now);
	strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
	
	this->_time = buffer;
	this->_password = pass;
	this->_serverFd = -1;
	this->_port = ft_stoi(port);

	for (std::size_t index = 0; index < 13; index++)
	{
		this->_commands.push_back(all_cmd[index]);
	}
}

Server::~Server() {}

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
				std::cout << "Accept Client" << std::endl;
				this->acceptClient();
			}
			else
			{
				std::cout << "Accept Data" << std::endl;
				this->acceptData(this->_polls[index].fd);
			}
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
	client_poll_fd.events = POLLIN;
	client_poll_fd.revents = 0;
	this->_polls.push_back(client_poll_fd);

	std::cout << "Client " << client_socket_fd << " connected" << std::endl;
}

void	Server::acceptData(int fd)
{
	char						buffer[1024];
	std::vector<std::string>	buffer_parse;
	ssize_t						data;

	std::memset(buffer, 0, sizeof(buffer));

	data = recv(fd, buffer, sizeof(buffer) - 1, 0);

	if (data <= 0)
	{
		std::cout << "Client " << fd << " disconnected" << std::endl;
		this->clearClient(fd);
		return ;
	}

	buffer[1023] = '\0';

	Client*	client = this->getClient(fd);
	if (client == NULL)
		return ;

	client->setReadBuffer(buffer);

	std::cout << "Buffer: " << client->getReadBuffer();

	//if (client->getsrcs/comands/ReadBuffer().find("\r\n") != std::string::npos)
	//{
	buffer_parse = ft_split(client->getReadBuffer(), "\n");
	for (std::size_t index = 0; index < buffer_parse.size(); index++)
	{
		this->execute(buffer_parse[index], fd);
	}
	if (this->getClient(fd) != NULL)
		client->getReadBuffer().clear();

	debug(*this);
	//}
}

typedef void (*FncPtr)(Server& server, int client_fd, const std::vector<std::string>& args);

void	Server::execute(std::string& cmd, int client_fd)
{
	std::vector<std::string>	args = ft_split_args(cmd);
	FncPtr						function_ptr_array[] = 
	{
		&cap,
		&pass,
		&nick,
		&user,
		&ping,
		&pong,
		&join,
		&invite,
		&kick,
		&part,
		&privmsg,
		&quit,
		&topic
	};

	for (std::size_t index = 0; index < this->getCommand().size(); index++)
	{
		if (args[0] == this->getCommand()[index])
		{
			std::cout << "Command: " << this->getCommand()[index] << std::endl;
			function_ptr_array[index](*this, client_fd, args);	// Be carefull i send the Command name also with the arguments !!!
			return ;
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
	for (std::size_t index = 0; index < this->_polls.size(); index++)
	{
		if (this->_polls[index].fd == fd)
		{
			this->_polls.erase(this->_polls.begin() + index);
		}
	}

	for (std::size_t index = 0; index < this->_clients.size(); index++)
	{
		if (this->_clients[index].getFd() == fd)
		{
			this->_clients[index].leaveAll(*this);
			close(this->_clients[index].getFd());
			this->_clients.erase(this->_clients.begin() + index);
		}
	}
}

void	Server::createChannel(const std::vector<std::string>& args)
{
	if (args.size() == 3)
	{
		Channel	channel(args[1], args[2]);
		this->_channels.push_back(channel);
		return ;
	}
	else
	{
		Channel	channel(args[1]);
		this->_channels.push_back(channel);
	}
}

void		Server::deleteChannel(const std::string& channelName)
{
	for (std::size_t index = 0; index < this->_channels.size(); index++)
	{
		if (this->_channels[index].getName() == channelName)
		{
			this->_channels.erase(this->_channels.begin() + index);
		}
	}
}


// SETTER
void	Server::setPassword(std::string pass)	{this->_password = pass;};
void	Server::setPort(int port) 				{this->_port = port;};
void	Server::setServerFd(int fd)				{this->_serverFd = fd;};
void	Server::setTime(std::string time) 		{this->_time = time;};

//Getter
int									Server::getPort(void) const 	{return this->_port;};
int									Server::getServerFd(void) const {return this->_serverFd;};
const std::string&					Server::getPassword(void) const {return this->_password;};
const std::string&					Server::getTime(void) const		{return this->_time;};
std::vector<Client>& 				Server::getClientsVector(void) 	{return this->_clients;};
std::vector<Channel>&				Server::getChannelVector(void)	{return this->_channels;};
const std::vector<std::string>&		Server::getCommand(void) const	{return this->_commands;};

Client*								Server::getClient(int fd)
{
	for (std::size_t index = 0; index < this->_clients.size(); index++)
	{
		if (this->_clients[index].getFd() == fd)
		{
			return (&this->_clients[index]);
		}
	}

	return (NULL);
}

Client*								Server::getClientByNick(const std::string& nickname)
{
	for (std::size_t index = 0; index < this->_clients.size(); index++)
	{
		if (this->_clients[index].getNickname() == nickname)
		{
			return (&this->_clients[index]);
		}
	}
	return (NULL);
}

Channel* 							Server::getChannelByName(const std::string& name)
{
	for (std::size_t index = 0; index < this->_channels.size(); index++)
	{
		if (this->_channels[index].getName() == name)
		{
			return (&this->_channels[index]);
		}
	}
	
	return (NULL);
}
