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
	if (!ft_strcmp(av[*k], "-c") && SET_FLAG(c))
	{
		ERR_QUIT_CON((*k + 1) >= ac, "Please Specify number of clients.");
		ERR_QUIT_CON((itmp = ft_atoi(av[++(*k)])) < 2,
			"Invalid number of clients.");
		g_env.settings.num_start_clients = itmp;
	}
	else if (!ft_strcmp(av[*k], "-t") && SET_FLAG(t))
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
	if (!ft_strcmp(av[*k], "-p") && SET_FLAG(p))
	{
		ERR_QUIT_CON((*k + 1) >= ac, "Please Specify port.");
		ERR_QUIT_CON((itmp = ft_atoi(av[++(*k)])) < 0 || itmp >= SHRT_MAX,
			"Invalid port number.");
		g_env.settings.port = itmp;
	}
	else if (!ft_strcmp(av[*k], "-x") && SET_FLAG(x))
	{
		ERR_QUIT_CON((*k + 1) >= ac, "Please Specify width.");
		ERR_QUIT_CON((itmp = ft_atoi(av[++(*k)])) < 10, "Invalid width.");
		g_env.settings.width = itmp;
	}
	else if (!ft_strcmp(av[*k], "-y") && SET_FLAG(y))
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

	ERR_QUIT_CON((++(*k)) >= ac, "Please specify team name");
	previous = NULL;
	itmp = 0;
	while (*k < ac && av[*k][0] != '-' && ++itmp)
	{
		if (!(team = (t_team *)ft_strnew(sizeof(t_team))))
		error_quit("Insufficient memory avaliable.");
		team->name = av[(*k)++];
		team->id = itmp;
		if (previous)
		previous->next = team;
		else
		g_env.settings.teams = team;
		previous = team;
	}
	--(*k);
	ERR_QUIT_CON(itmp < 1, "Please specify team name");
	g_env.settings.num_teams = itmp;
	return (1);
}

static void	print_help(char **av)
{
	printf("Usage: %s -p <port> -x <width> -y <height> ", av[0]);
	printf("-n <team> [<team>] [<team>] ... -c <nb> -t <t>\n\n");
	printf("-p\tport number\n");
	printf("-x\tworld width\n");
	printf("-y\tworld height\n");
	printf("-n\tteam_name_1 team_name_2 ...\n");
	printf("-c\tnumber of clients authorized at the beginning of the game\n");
	printf("-t\ttime unit divider (the greater, the faster the game runs)\n");
	printf("-h\t(--help) print this help menu\n");
	printf("\n");
	exit(0);
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
		else if (!ft_strcmp(av[k], "-n") && SET_FLAG(n))
			parse_teams(ac, av, &k, itmp);
		else if (!ft_strcmp(av[k], "-h") || !ft_strcmp(av[k], "--help"))
			print_help(av);
		else if (is_input_flag_set(av[k]))
			error_quit(ft_strjoin(av[k], " flag already set."));
		else
			error_quit(ft_strjoin("Unknown paramiter: ", av[k]));
	}
}
