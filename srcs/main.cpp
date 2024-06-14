/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gurousta <gurousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:09:02 by gurousta          #+#    #+#             */
/*   Updated: 2024/06/14 20:17:15 by gurousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

int	main(void)
{
	Server	server;

	try
	{
		/*signal(SIGQUIT, Server::signalHandler);
		signal(SIGINT, Server::signalHandler);*/
		server.serverInit();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (EXIT_FAILURE);
	}

	while (1);
	
	return (EXIT_SUCCESS);
}