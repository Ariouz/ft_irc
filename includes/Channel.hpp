/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:25:23 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/18 15:10:21 by vicalvez         ###   ########.fr       */
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
		int							_id;
		std::string					_name;
		ChannelSettings*			_settings;
		std::vector<Client*>		_clients;
		std::vector<Client*>		_operators;
		std::vector<Client*>		_whitelist;

	public:
		Channel(Server& server, const std::string& name);
		~Channel();

		void 						addClient(Client* client);
		void 						removeClient(int clientFd);
	
		void 						addOperator(Client* ope);
		void 						removeOperator(int operatorFd);
	
		void						addWhitelisted(Client* client);
		void						removeWhitelisted(int clientFd);
		bool						isWhitelisted(int clientFd) const;
	
		int 						getId() const;
		ChannelSettings* 			getSettings(void);
		bool 						isOperator(int clientFd) const;
		const std::string&			getName(void) const;
		std::vector<Client*>		getClients(void);
};

#endif