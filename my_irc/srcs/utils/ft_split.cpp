/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 20:10:45 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/19 10:14:08 by laguigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

std::vector<std::string>	ft_split(std::string string, std::string delimiter)
{
	std::vector<std::string>	result;
	std::string					to_push;
	std::size_t					pos = 0;

	while ((pos = string.find(delimiter)) != std::string::npos)
	{
		to_push = string.substr(0, pos);
		result.push_back(to_push);
		string.erase(0, pos + 1);
	}

	return (result);
}

std::vector<std::string>	ft_split_args(std::string string)
{
	std::vector<std::string>	result;
	std::istringstream			iss(string);
	std::string					word;

	while (iss >> word)
	{
		result.push_back(word);
	}

	return (result);
}