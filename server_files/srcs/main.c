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

void	tend_clients(struct timeval reff)
{
	struct timeval	now;
	int				rem;

	gettimeofday(&now, NULL);
	rem = abs(reff.tv_usec - now.tv_usec);
	while (rem < (1000000 / g_env.settings.fps))
	{
		prep_client_sockets();
		reff.tv_sec = (g_env.settings.fps == 1) ? 1 : 0;
		reff.tv_usec = (g_env.settings.fps == 1) ? 0 : 1000000 / \
			g_env.settings.fps - rem;
		ACTIVE_SOCK = select(MASTER_MAX_SD + 1, &READ_FDS, NULL, NULL, \
			&reff);
		if (ACTIVE_SOCK < 0)
			error_quit("Failed to monitor sockets.");
		if (FD_ISSET(MASTER_SOCK, &READ_FDS))
			accept_new_client();
		if (ACTIVE_SOCK > 0)
			manage_clients();
		gettimeofday(&now, NULL);
		rem = abs(reff.tv_usec - now.tv_usec);
	}
}

void	main_loop(void)
{
	struct timeval	reff;

	while (1)
	{
		gettimeofday(&reff, NULL);
		run_iteration();
		tend_clients(reff);
	}
}

int		main(int ac, char **av)
{
	ft_bzero(&g_env, sizeof(t_env));
	parse_arguments(ac, av);
	set_defults();
	init_main_socket(g_env.settings.port);
	init_gameplay();
	srand(time(NULL));
	main_loop();
	return (0);
}
