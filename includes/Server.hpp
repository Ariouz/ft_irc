/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:28:36 by gurousta          #+#    #+#             */
/*   Updated: 2024/06/17 18:14:26 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "ft_irc.hpp"

class Client;
class Channel;
class CommandManager;

class Server
{
	private:
		int							_port;
		int							_serverFd;
		std::string					_password;
		std::vector<Client>			_clients;
		std::vector<Channel>		_channels;
		std::vector<struct pollfd>	_polls;
		CommandManager*				_commandManager;

	public:
		Server(std::string port, std::string pass);
		~Server();

		void					serverInit(void);
		void					loop(void);
		void					closeFd(void);
		void					clearClient(int fd);
		void					acceptClient(void);
		void					acceptData(int fd);
		void					handlePollout(int fd);
		void					handlePoller(int fd);

		void					setPassword(std::string pass);
		void					setPort(int port);
		void					setServerFd(int fd);

		void					createChannel(void);

		int						getPort(void) const;
		int						getServerFd(void) const;
		const std::string&		getPassword(void) const;
		Client* 				getClient(int clientFd);
		Channel* 				getChannel(int channelId);
		CommandManager* 		getCommandManager(void);
		std::vector<Client> 	getClients(void) const;
		std::vector<Channel> 	getChannels(void) const;
		
		
		bool				checkAuth(Client& client);
};

#endif