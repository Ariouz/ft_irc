/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:25:23 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/17 11:33:14 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "ft_irc.hpp"
# include "ChannelSettings.hpp"

class Client;
class Server;
class ChannelSettings;

class Channel
{
	private:
		int						_id;
		ChannelSettings			_settings;
		std::vector<Client>		_clients;
		std::vector<Client>		_operators;

	public:
		Channel(const Server& server);
		~Channel();

		void 					addClient(const Client& client);
		void 					removeClient(int clientFd);

		void 					addOperator(const Client& ope);
		void 					removeOperator(int operatorFd);

		int 					getId() const;
		const ChannelSettings& 	getSettings(void) const;
		bool 					isOperator(int clientFd) const;
};

#endif