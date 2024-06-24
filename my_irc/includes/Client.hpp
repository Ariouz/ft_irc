/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:24:20 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/24 16:36:08 by laguigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "ft_irc.hpp"

# define AUTH_ERR -1
# define AUTH_INIT 0
# define AUTH_PASS 1
# define AUTH_NICK 2
# define AUTH_USER 3
# define AUTH_OK   4

class Server;

class Client
{
	private:
		int			_fd;
		std::string	_username;
		std::string	_nickname;
		std::string	_ipAddr;
		std::string	_sendBuffer;
		std::string	_readBuffer;
		std::string	_mode;
		int			_authStatus;

	public:
		Client();
		~Client();

		void				setFd(int fd);
		void				setUsername(std::string username);
		void				setNickname(std::string nickname);
		void				setIpAddr(std::string ipAddr);
		void				setSendBuffer(std::string buffer);
		void				setReadBuffer(std::string buffer);
		void				setAuthStatus(int auth);
		
		void				leaveAll(Server& server);

		int					getFd(void) const;
		std::string&		getUsername(void);
		std::string&		getNickname(void);
		std::string&		getIpAddr(void);
		std::string&		getSendBuffer(void);
		std::string&		getReadBuffer(void);
		int					getAuthStatus(void) const;
		
		bool				isAuthenticated(void) const;
		bool				checkAuth(void) const;
};


#endif