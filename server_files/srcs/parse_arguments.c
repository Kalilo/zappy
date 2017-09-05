/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 10:28:10 by khansman          #+#    #+#             */
/*   Updated: 2017/09/05 10:28:10 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

static char	parse_basic_arg2(int ac, char **av, int *k, int itmp)
{
	if (!ft_strcmp(av[*k], "-c"))
	{
		ERR_QUIT_CON((*k + 1) >= ac, "Please Specify number of clients.");
		ERR_QUIT_CON((itmp = ft_atoi(av[++(*k)])) < 10,
			"Invalid number of clients.");
		g_env.settings.num_start_clients = itmp;
	}
	else if (!ft_strcmp(av[*k], "-t"))
	{
		ERR_QUIT_CON((*k + 1) >= ac, "Please Specify time unit.");
		ERR_QUIT_CON((itmp = ft_atoi(av[++(*k)])) < 10,
			"Invalid time unit.");
		g_env.settings.fps = itmp;
	}
	else
		return (0);
	return (1);
}

static char	parse_basic_arg(int ac, char **av, int *k, int itmp)
{
	if (!ft_strcmp(av[*k], "-p"))
	{
		ERR_QUIT_CON((*k + 1) >= ac, "Please Specify port.");
		ERR_QUIT_CON((itmp = ft_atoi(av[++(*k)])) < 0 || itmp >= SHRT_MAX,
			"Invalid port number.");
		g_env.settings.port = itmp;
	}
	else if (!ft_strcmp(av[*k], "-x"))
	{
		ERR_QUIT_CON((*k + 1) >= ac, "Please Specify width.");
		ERR_QUIT_CON((itmp = ft_atoi(av[++(*k)])) < 10, "Invalid width.");
		g_env.settings.width = itmp;
	}
	else if (!ft_strcmp(av[*k], "-y"))
	{
		ERR_QUIT_CON((*k + 1) >= ac, "Please Specify height.");
		ERR_QUIT_CON((itmp = ft_atoi(av[++(*k)])) < 10, "Invalid height.");
		g_env.settings.height = itmp;
	}
	else
		return (parse_basic_arg2(ac, av, k, itmp));
	return (1);
}

static char	parse_teams(int ac, char **av, int *k, int itmp)
{
	t_team	*team;
	t_team	*previous;

	ERR_QUIT_CON((*k + 1) >= ac, "Please Specify number of teams");
	ERR_QUIT_CON((itmp = ft_atoi(av[++(*k)])) < 1,
		"Invalid number of teams.");
	g_env.settings.num_teams = itmp;
	previous = NULL;
	while (itmp-- && ++k)
	{
		ERR_QUIT_CON((*k + 1) >= ac, "Please specify team's name");
		if (!(team = (t_team *)ft_strnew(sizeof(t_team))))
			error_quit("Insufficient memory avaliable.");
		team->name = av[(*k)];
		team->id = itmp;
		if (previous)
			previous->next = team;
		else
			g_env.settings.teams = team;
		previous = team;
	}
}

void		parse_arguments(int ac, char **av)
{
	int		k;
	int		itmp;

	k = 0;
	itmp = 0;
	while (++k < ac)
	{
		if (parse_basic_arg(ac, av, &k, itmp))
			continue ;
		else if (!ft_strcmp(av[k], "-n"))
			parse_teams(ac, av, &k, itmp);
	}
}
