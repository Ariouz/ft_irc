/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurousta <gurousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:28:28 by gurousta          #+#    #+#             */
/*   Updated: 2024/06/14 18:31:28 by gurousta         ###   ########.fr       */
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

	public:
		Client();
		~Client();

		void	setFd(int fd);
		void	setUsername(std::string username);
		void	setNickname(std::string nickname);
		void	setIpAddr(std::string ipAddr);

		int					getFd(void) const;
		const std::string&	getUsername(void) const;
		const std::string&	getNickname(void) const;
		const std::string&	getIpAddr(void) const;
};


#endif