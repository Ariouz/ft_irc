/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurousta <gurousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:28:36 by gurousta          #+#    #+#             */
/*   Updated: 2024/06/14 20:13:39 by gurousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "ft_irc.hpp"

typedef struct	s_poll_fd	//	Used for monitoring multiple file descriptor for I/O event
{
	int			fd;			//	File descriptor
	short		event;		//	Bitmask that specifies the events(read, write, error...) for the given fd
	short		revent;		//	Bitmask that specifies the events that occurred for the given fd
}			t_poll_fd;

class Client;

class Server
{
	private:
		int							_port;
		int							_serverFd;
		//static bool					_serverSignal;
		std::vector<Client>			_clients;
		std::vector<t_poll_fd>		_polls;

	public:
		Server();
		~Server();

		//static void	signalHandler(int signum);

		void	serverInit(void);
		void	closeFd(void);

		void	setPort(int port);
		void	setServerFd(int fd);

		int		getPort(void) const;
		int		getServerFd(void) const;
};

#endif