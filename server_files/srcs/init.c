/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 07:57:10 by khansman          #+#    #+#             */
/*   Updated: 2017/07/18 07:57:11 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

/*
** Signals:
** Discarded: 13
** Kill program: 2
*/

void	sig_listener(int signo)
{
	printf("\rgot signal: %d                    \n", signo);//debug
	if (signo == SIGPIPE || signo == SIGURG || signo == SIGCONT ||
			signo == SIGCHLD || signo == SIGIO)
		return ;
	close(MASTER_SOCK);
	exit(0);
}

void	sig_setter(void)
{
	int		k;

	k = -1;
	while (++k < 28)
		signal(k, sig_listener);
}

char	init_main_socket(int port)
{
	if (port <= 0 || SHRT_MAX <= port)
		error_quit("Invalid port number given.");
	if ((MASTER_SOCK = socket(AF_INET, SOCK_STREAM, 0)) == 0)
		error_quit("Failed to open master socket.");
	sig_setter();
	if (setsockopt(MASTER_SOCK, SOL_SOCKET, SO_REUSEADDR, (char *)&MASTER_OPT,
			sizeof(MASTER_OPT)) < 0)
		error_quit("Failed to set master socket to allow multiple connections");
	MASTER_ADDR.sin_family = AF_INET;
	MASTER_ADDR.sin_addr.s_addr = INADDR_ANY;
	MASTER_ADDR.sin_port = htons(port);
	if (bind(MASTER_SOCK, (t_sock_addr *)&MASTER_ADDR, sizeof(MASTER_ADDR)) < 0)
		error_quit("Falied to bind master socket to port.");
	if (listen(MASTER_SOCK, 3) < 0)
		error_quit("Failed to run listen on master socket");
	MASTER_ADDRLEN = sizeof(MASTER_ADDR);
	return (1);
}

void	set_defults(void)
{
	t_team	*team;

	if (!INPUT_FLAG(p))
		g_env.settings.port = 4000;
	if (!INPUT_FLAG(x))
		g_env.settings.width = 100;
	if (!INPUT_FLAG(y))
		g_env.settings.height = 100;
	if (!INPUT_FLAG(c))
		g_env.settings.num_start_clients = 10;
	if (!INPUT_FLAG(t))
		g_env.settings.fps = 30;
	if (!INPUT_FLAG(n))
	{
		if (!(team = (t_team *)ft_strnew(sizeof(t_team))))
			error_quit("Insufficient memory avaliable.");
		team->name = "Team00";
		team->id = 1;
		g_env.settings.num_teams = 1;
		g_env.settings.teams = team;
	}
}

void	init_gameplay(void)
{
	int		k;

	k = -1;
	if (!(g_env.map = (t_tile **)ft_strnew(sizeof(t_tile *) * (G_WIDTH + 1))))
		error_quit("Insufficient memory avaliable.");
	while ((unsigned int)++k < G_HEIGHT)
		if (!(g_env.map[k] = (t_tile *)ft_strnew(sizeof(t_tile) * (G_HEIGHT + 1))))
			error_quit("Insufficient memory avaliable.");
	populate_map();
	g_env.play = 1;
}
