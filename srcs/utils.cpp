/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicalvez <vicalvez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 14:51:13 by laguigue          #+#    #+#             */
/*   Updated: 2024/06/17 10:09:41 by vicalvez         ###   ########.fr       */
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