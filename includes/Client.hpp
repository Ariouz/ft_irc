/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:28:28 by gurousta          #+#    #+#             */
/*   Updated: 2024/06/15 23:30:21 by laguigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "ft_irc.hpp"

class Client
{
	private:
		int			_fd;
		std::string	_username;
		std::string	_nickname;
		std::string	_ipAddr;
		std::string	_sendBuffer;
		std::string	_readBuffer;

	public:
		Client();
		~Client();

		void	setFd(int fd);
		void	setUsername(std::string username);
		void	setNickname(std::string nickname);
		void	setIpAddr(std::string ipAddr);
		void	setSendBuffer(std::string buffer);

		int					getFd(void) const;
		const std::string&	getUsername(void) const;
		const std::string&	getNickname(void) const;
		const std::string&	getIpAddr(void) const;
		std::string&		getSendBuffer(void);
};


#endif