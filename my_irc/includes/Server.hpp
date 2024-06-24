/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:22:58 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/24 13:56:41 by laguigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "ft_irc.hpp"

class Client;
//class Channel;
//class CommandManager;

class Server
{
	private:
		int							_port;
		int							_serverFd;
		std::string					_password;
		std::string					_time;
		std::vector<std::string>	_commands;
		std::vector<Client>			_clients;
		std::vector<Channel>		_channels;
		std::vector<struct pollfd>	_polls;

	public:
		Server(std::string port, std::string pass);
		~Server();

		void					serverInit(void);
		void					loop(void);
		void					closeFd(void);
		void					clearClient(int fd);
		void					acceptClient(void);
		void					acceptData(int fd);

		void					setPassword(std::string pass);
		void					setTime(std::string time);
		void					setPort(int port);
		void					setServerFd(int fd);

		void					createChannel(const std::vector<std::string>& args);
		void					deleteChannel(const std::string& channelName);

		int									getPort(void) const;
		int									getServerFd(void) const;
		const std::string&					getPassword(void) const;
		const std::string&					getTime(void) const;
		const std::vector<std::string>&		getCommand(void) const;
		Client* 							getClient(int clientFd);
		Client*								getClientByNick(const std::string& nickname);
		Channel* 							getChannelByName(const std::string& name);
		std::vector<Client>& 				getClientsVector(void);
		std::vector<Channel>&				getChannelVector(void);
		//std::vector<Channel*> 			getChannels(void) const;
		
		
		//bool				checkAuth(Client& client);

		void				execute(std::string& cmd, int client_fd);
};

#endif