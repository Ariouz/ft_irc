/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:28:14 by gurousta          #+#    #+#             */
/*   Updated: 2024/06/15 23:27:20 by laguigue         ###   ########.fr       */
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
# include "Client.hpp"
# include "Server.hpp"
//# include "Channel.hpp"

//	Simply for signal
extern bool		server_signal;

/*			Function usefull for the project					*/

int	ft_stoi(const std::string& string);

#endif