/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:28:36 by gurousta          #+#    #+#             */
/*   Updated: 2024/06/15 23:27:46 by laguigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "ft_irc.hpp"
class Client;

//class Channel;

class Server
{
	private:
		int							_port;
		int							_serverFd;
		std::string					_password;
		std::vector<Client>			_clients;
		//std::vector<Channel>		_channels;
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
		void					handlePollout(int fd);
		void					handlePoller(int fd);

		void					setPassword(std::string pass);
		void					setPort(int port);
		void					setServerFd(int fd);

		int						getPort(void) const;
		int						getServerFd(void) const;
		const std::string&		getPassword(void) const;
};

#endif