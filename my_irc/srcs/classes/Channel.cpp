/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 13:17:17 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/24 17:23:27 by laguigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"
#include "../../includes/Channel.hpp"

Channel::Channel(const std::string& name) : _name(name), _mode("+") {}

Channel::Channel(const std::string& name, const std::string& pass) : _name(name), _channelPass(pass), _mode("+") {}

Channel::~Channel() {}

void	Channel::addClient(Client* client)
{
	this->_clients.push_back(client);	
}

void	Channel::addOperator(std::string& username)
{
	this->_operator.push_back(username);
}

void	Channel::removeClient(const std::string& user_name)
{
	for (std::size_t index = 0; index < this->_clients.size(); index++)
	{
		if (this->_clients[index]->getUsername() == user_name)
		{
			if (this->isOperator(this->_clients[index]->getUsername()))
			{
				this->removeOperator(this->_clients[index]->getUsername());
			}
			this->_clients.erase(this->_clients.begin() + index);
		}
	}
}

void	Channel::removeOperator(const std::string& username)
{
	for (std::size_t index = 0; index < this->_operator.size(); index++)
	{
		if (this->_operator[index] == username)
		{
			this->_operator.erase(this->_operator.begin() + index);
		}
	}
}

void	Channel::removeWhitelist(const std::string& username)
{
	for (std::size_t index = 0; index < this->_whitelist.size(); index++)
	{
		if (this->_whitelist[index] == username)
		{
			this->_whitelist.erase(this->_operator.begin() + index);
		}
	}
}

bool	Channel::isOperator(const std::string& username)
{
	for (std::size_t index = 0; index < this->_operator.size(); index++)
	{
		if (this->_operator[index] == username)
		{
			return (true);
		}
	}
	return (false);
}

bool	Channel::isWhitelisted(const std::string& username)
{
	for (std::size_t index = 0; index < this->_whitelist.size(); index++)
	{
		if (this->_whitelist[index] == username)
		{
			return (true);
		}
	}
	return (false);
}

bool	Channel::isClient(const std::string& username)
{
	for (std::size_t index = 0; index < this->_clients.size(); index++)
	{
		if (this->_clients[index]->getUsername() == username)
		{
			return (true);
		}
	}
	return (false);
}

//SETTER
void	Channel::setTopic(const std::string& topic)				{this->_topic = topic;};
void	Channel::setChannelPass(const std::string& pass)		{this->_channelPass = pass;};
void	Channel::setMaxUser(const int limit)					{this->_maxUser = limit;};
//void	Channel::setInviteOnly(bool to_set)						{this->_inviteOnly = to_set;};
//void	Channel::setTopicRestrict(bool to_set)					{this->_topicRestrict = to_set;};

//GETTER
int							Channel::getLimit(void) const		{return this->_maxUser;};
//bool						Channel::getInviteOnly(void)		{return this->_inviteOnly;};
//bool						Channel::getTopicRestrict(void)		{return this->_topicRestrict;};
const std::string&			Channel::getName(void) const		{return this->_name;};
std::string&				Channel::getMode(void)				{return this->_mode;};
std::string&				Channel::getTopic(void)				{return this->_topic;};
std::string&				Channel::getPass(void)				{return this->_channelPass;};
std::vector<Client*>&		Channel::getClientVector(void)		{return this->_clients;};
std::vector<std::string>&	Channel::getOperatorVector(void)	{return this->_operator;};
std::vector<std::string>&	Channel::getWhitelistVector(void)	{return this->_whitelist;};
std::vector<std::string>&	Channel::getKickVector(void)		{return this->_kick;};