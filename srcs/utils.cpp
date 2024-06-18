/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 14:51:13 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/18 18:04:27 by vicalvez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

int	ft_stoi(const std::string& string)
{
	std::stringstream	ss(string);
	int					result;

	ss >> result;

	return (result);
}

std::vector<std::string> splitToVector(const std::string& str)
{
    std::vector<std::string>    result;
    std::istringstream          iss(str);
    std::string                 word;

    while (iss >> word) {
        result.push_back(word);
    }

    return result;
}

std::vector<std::string> splitByCr(const std::string& input)
{
    std::vector<std::string>    result;
    std::istringstream          iss(input);
    std::string                 line;

    while (std::getline(iss, line, '\n'))
    {
        if (!line.empty() && line[line.size() - 1] == '\r')
        {
            line.resize(line.size() - 1);
        }
        result.push_back(line);
    }

    return result;
}

void    sendBuffer(Client& client)
{
    send(client.getFd(), client.getSendBuffer().c_str(), client.getSendBuffer().size(), 0);
    client.getSendBuffer().clear();
}

std::string vectorToString(const std::vector<std::string> vec)
{
    std::string res = "";
    for (std::size_t index = 0; index < vec.size(); index++)
    {
        res += vec[index] + " ";
    }
    if (res[res.size() - 1] == ' ') res = res.substr(0, res.size() - 1);
    return res;
}