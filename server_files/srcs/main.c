/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 10:26:56 by khansman          #+#    #+#             */
/*   Updated: 2017/09/05 10:26:58 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define SERVER_MAIN
#include "../includes/server.h"

void	main_loop(void)
{
	while (1)
	{
		prep_client_sockets();
		//change to have a delay timer...
		// ACTIVE_SOCK = select(MASTER_MAX_SD + 1, &READ_FDS, NULL, NULL, NULL);
		if (ACTIVE_SOCK < 0)
			error_quit("Failed to monitor sockets.");
		if (FD_ISSET(MASTER_SOCK, &READ_FDS))
			accept_new_client();
		manage_clients();
	}
}

int		main(int ac, char **av)
{
	ft_bzero(&g_env, sizeof(t_env));
	parse_arguments(ac, av);
	set_defults();
	init_main_socket(g_env.settings.port);
	main_loop();
	return (0);
}
