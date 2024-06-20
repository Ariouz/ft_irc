/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:28:36 by gurousta          #+#    #+#             */
/*   Updated: 2024/06/20 11:41:29 by vicalvez         ###   ########.fr       */
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
		std::vector<Client*>		_clients;
		std::vector<Channel*>		_channels;
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

		void					setPassword(std::string pass);
		void					setPort(int port);
		void					setServerFd(int fd);

		void					createChannel(const std::string& name);
		void					deleteChannel(Channel* channel);

		int						getPort(void) const;
		int						getServerFd(void) const;
		const std::string&		getPassword(void) const;
		Client* 				getClient(int clientFd);
		Client* 				getClientByNickname(const std::string& name);
		Channel* 				getChannel(int channelId);
		Channel* 				getChannelByName(const std::string& name);
		CommandManager& 		getCommandManager(void);
		std::vector<Client*>& 	getClients(void);
		std::vector<Channel*>& 	getChannels(void);
		
		
		bool				checkAuth(Client& client);
};

#endif