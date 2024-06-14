/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurousta <gurousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:28:14 by gurousta          #+#    #+#             */
/*   Updated: 2024/06/14 20:08:49 by gurousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP
# define FT_IRC_HPP

/*			Includes usefull for the project					*/

# include <iostream>
# include <string>
# include <algorithm>
# include <vector>
# include <stdint.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <unistd.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <poll.h>
# include "Client.hpp"
# include "Server.hpp"


typedef struct s_addr
{
	in_addr_t	addr;
}		t_addr;

typedef struct	s_socket_addr 	//	Contain information for the server socket
{
	sa_family_t	family;			//	Family address for IPv4, normally set to AF_INET
	in_port_t	port;			//	A 16 bits representing the port in network byte order, we use htons() to convert 16 bits usigned short form host byte order to network byte order
	t_addr		addr;			//	IPv4 address in network byte order, normally set to INADDR_ANY
	char		padding[8];		//	Usefull only for the padding of the struct
}			t_socketaddr;

/*typedef struct	s_poll_fd	//	Used for monitoring multiple file descriptor for I/O event
{
	int			fd;			//	File descriptor
	short		event;		//	Bitmask that specifies the events(read, write, error...) for the given fd
	short		revent;		//	Bitmask that specifies the events that occurred for the given fd
}			t_poll_fd;*/

#endif