/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   team_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 15:24:36 by khansman          #+#    #+#             */
/*   Updated: 2017/09/11 15:24:58 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

t_team		*find_client_team(t_client *client)
{
	t_team		*team;

	team = g_env.settings.teams;
	while (team)
	{
		if (team->id == client->team_id)
			return (team);
		team = team->next;
	}
	return (NULL);
}

t_team		*find_team(char *name)
{
	t_team		*team;

	team = g_env.settings.teams;
	if (!name)
		return (NULL);
	while (team)
	{
		if (!ft_strcmp(name, team->name))
			return (team);
		team = team->next;
	}
	return (NULL);
}

char		has_team_won(int team_id)
{
	t_client	*client;
	int			level_eights;

	level_eights = 0;
	client = g_env.clients;
	while (client)
	{
		if (client->team_id == team_id && client->level >= 8)
			level_eights++;
		client = client->next;
	}
	return (level_eights >= 6);
}

void		set_team_connections(void)
{
	t_team		*team;
	int			avaliable_conns;

	avaliable_conns = g_env.settings.num_start_clients / \
		g_env.settings.num_teams;
	team = g_env.settings.teams;
	while (team)
	{
		team->avaliable_cons = avaliable_conns;
		team = team->next;
	}
}
