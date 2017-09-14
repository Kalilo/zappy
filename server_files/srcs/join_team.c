/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_team.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 10:38:42 by khansman          #+#    #+#             */
/*   Updated: 2017/09/14 10:38:43 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

char	join_team(t_client *client, char *team)
{
	t_team 	*t;

	t = g_env.settings.teams;
	while (t)
	{
		if (!ft_strcmp(t->name, team))
			break;
		t = t->next;
	}
	if (!team || (t->avaliable_cons < 1 && !g_env.settings.num_unused_conn))
		return (0);
	if (t->eggs && ((client->delay = -600) || 1))
		client->pos = hatch_egg(find_team(team));
	else if (g_env.settings.num_unused_conn && \
			(g_env.settings.num_unused_conn--))
		client->pos = (t_coord){rand() % G_WIDTH, rand() % G_HEIGHT};
	else
		return (0);
	t->avaliable_cons--;
	t->num_members++;
	client->direction = (rand() & 0b11) << 1;
	client->level = 1;
	client->team_id = t->id;
	client->life = 1260;
	return (1);
}
