/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laguigue <laguigue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:09:02 by gurousta          #+#    #+#             */
/*   Updated: 2024/06/15 19:16:29 by laguigue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_irc.hpp"

bool	server_signal = false;


void	signalHandler(int signum)
{
	(void) signum;
	std::cout << std::endl << "Signal received!" << std::endl;
	server_signal = true;
}

int	main(int argc, char** argv)
{
	if (argc != 3)
	{
		std::cout << "Correct usage: ./ircserv [port] [password]" << std::endl;
		return (EXIT_FAILURE);
	}

	Server	server(argv[1], argv[2]);
	server_signal = false;
	signal(SIGQUIT, signalHandler);
	signal(SIGINT, signalHandler);

	try
	{
		server.serverInit();
		
		while (server_signal == false)
		{
			server.loop();
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (EXIT_FAILURE);
	}
		
	return (EXIT_SUCCESS);
}