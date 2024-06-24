/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorToString.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:56:34 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/24 12:56:59 by laguigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.hpp"

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