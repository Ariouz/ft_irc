/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:28:14 by gurousta          #+#    #+#             */
/*   Updated: 2024/06/17 19:06:55 by vicalvez         ###   ########.fr       */
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
# include "Channel.hpp"

//	Simply for signal
extern bool		server_signal;

/*			Function usefull for the project					*/

int	                        ft_stoi(const std::string& string);
std::vector<std::string>    splitToVector(const std::string& str);
std::vector<std::string>    splitByCr(const std::string& input);

#endif