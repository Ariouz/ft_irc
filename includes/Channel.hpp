/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:25:23 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/17 17:33:28 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "ft_irc.hpp"

class Client;
class Server;
class ChannelSettings;

class Channel
{
	private:
		int						_id;
		//ChannelSettings			_settings;
		std::vector<Client>		_clients;
		std::vector<Client>		_operators;

	public:
		Channel(Server& server);
		~Channel();

		void 					addClient(const Client& client);
		void 					removeClient(int clientFd);

		void 					addOperator(const Client& ope);
		void 					removeOperator(int operatorFd);

		int 					getId() const;
		//ChannelSettings* 		getSettings(void);
		bool 					isOperator(int clientFd) const;
};

#endif