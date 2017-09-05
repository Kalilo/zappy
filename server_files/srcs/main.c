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

void	set_defults(void)
{
	t_team	*team;

	g_env.settings.port = g_env.settings.port || 4000;
	g_env.settings.width = g_env.settings.width || 100;
	g_env.settings.height = g_env.settings.height || 100;
	g_env.settings.num_teams = g_env.settings.num_teams || 1;
	g_env.settings.num_start_clients = g_env.settings.num_start_clients || 10;
	g_env.settings.fps = g_env.settings.fps || 30;
	if (!g_env.settings.teams)
	{
		if (!(team = (t_team *)ft_strnew(sizeof(t_team))))
			error_quit("Insufficient memory avaliable.");
		team->name = "Team00";
		team->id = 0;
		g_env.settings.teams = team;
	}
}

int		main(int ac, char **av)
{
	ft_bzero(&g_env, sizeof(t_env));
	parse_arguments(ac, av);
	set_defults();
	return (0);
}
