/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:21:54 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/24 16:34:18 by laguigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP
# define FT_IRC_HPP

/*			Includes usefull for the project					*/

# include <iostream>
# include <string>
# include <algorithm>
# include <vector>
# include <fstream>
# include <sstream>
# include <cstring>
# include <ctime>
# include <bitset>
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

# include "Message.hpp"
# include "Client.hpp"
# include "Channel.hpp"
# include "Server.hpp"

//	Simply for signal
extern bool		server_signal;

/*			Command Function									*/

void	cap(Server& server, int client_fd, const std::vector<std::string>& args);
void	pass(Server& server, int client_fd, const std::vector<std::string>& args);
void	nick(Server& server, int client_fd, const std::vector<std::string>& args);
void	user(Server& server, int client_fd, const std::vector<std::string>& args);
void	ping(Server& server, int client_fd, const std::vector<std::string>& args);
void	pong(Server& server, int client_fd, const std::vector<std::string>& args);
void	join(Server& server, int client_fd, const std::vector<std::string>& args);
void	invite(Server& server, int client_fd, const std::vector<std::string>& args);
void	kick(Server& server, int client_fd, const std::vector<std::string>& args);
void	part(Server& server, int client_fd, const std::vector<std::string>& args);
void	privmsg(Server& server, int client_fd, const std::vector<std::string>& args);
void	quit(Server& server, int client_fd, const std::vector<std::string>& args);
void	topic(Server& server, int client_fd, const std::vector<std::string>& args);
void    mode(Server& server, int client_fd, const std::vector<std::string>& args);


/*			Function usefull for the project					*/

void    					sendBuffer(Client& client);
int							ft_stoi(const std::string& string);
std::string                 vectorToString(const std::vector<std::string> vec);
std::vector<std::string>	ft_split(std::string string, std::string delimiter);
std::vector<std::string>	ft_split_args(std::string string);

#endif