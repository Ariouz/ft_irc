/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:24:26 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/24 17:22:51 by laguigue         ###   ########.fr       */
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
		std::string					_name;
		std::vector<Client*>		_clients;
		std::vector<std::string>	_operator;
		std::vector<std::string>	_whitelist;
		std::vector<std::string>	_kick;
		std::string					_topic;
		std::string					_channelPass;
		std::string					_mode;
		int							_maxUser;
		//bool						_inviteOnly;
		//bool						_topicRestrict;

	public:
		Channel(const std::string& name);
		Channel(const std::string& name, const std::string& pass);
		~Channel();

		void	addClient(Client* client);
		void	addOperator(std::string& username);
		void	removeClient(const std::string& username);
		void	removeOperator(const std::string& username);
		void	removeWhitelist(const std::string& username);

		bool	isOperator(const std::string& username);
		bool	isWhitelisted(const std::string& username);
		bool	isClient(const std::string& username);

		//SETTER
		void	setTopic(const std::string& topic);
		void	setChannelPass(const std::string& pass);
		void	setMaxUser(const int limit);
		//void	setInviteOnly(bool to_set);
		//void	setTopicRestrict(bool to_set);

		//GETTER
		int							getLimit(void) const;
		//bool						getInviteOnly(void);
		//bool						getTopicRestrict(void);
		const std::string&			getName(void) const;
		std::string&				getMode(void);
		std::string&				getTopic(void);
		std::string&				getPass(void);
		std::vector<Client*>&		getClientVector(void);
		std::vector<std::string>&	getOperatorVector(void);
		std::vector<std::string>&	getWhitelistVector(void);
		std::vector<std::string>&	getKickVector(void);
		

};

#endif