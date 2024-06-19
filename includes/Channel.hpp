/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:25:23 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/19 11:41:47 by vicalvez         ###   ########.fr       */
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
		bool						isClient(int clientFd) const;
	
		void 						addOperator(Client* ope);
		void 						removeOperator(int operatorFd);
		bool 						isOperator(int clientFd) const;
	
		void						addWhitelisted(Client* client);
		void						removeWhitelisted(int clientFd);
		bool						isWhitelisted(int clientFd) const;
	
		int 						getId() const;
		ChannelSettings* 			getSettings(void);
		const std::string&			getName(void) const;
		std::vector<Client*>&		getClients(void);
};

#endif