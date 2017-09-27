/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   egg_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 11:10:59 by khansman          #+#    #+#             */
/*   Updated: 2017/09/12 11:11:00 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

t_egg	*new_egg(t_client *client)
{
	static int	id_count;
	t_egg		*egg;

	egg = (t_egg *)ft_strnew(sizeof(t_egg));
	egg->id = ++id_count;
	egg->team_id = client->team_id;
	egg->pos = client->pos;
	egg->life = 1260;
	return (egg);
}

int		lay_egg(t_client *client)
{
	t_egg		*egg;
	t_egg		*tmp;
	t_team		*team;

	egg = MAP(client->pos.x, client->pos.y).eggs;
	while (egg && egg->next)
		egg = egg->next;
	tmp = new_egg(client);
	if (++g_env.settings.num_eggs && egg)
		egg->next = tmp;
	else
		MAP(client->pos.x, client->pos.y).eggs = tmp;
	team = find_client_team(client);
	team->avaliable_cons++;
	egg = ft_memalloc(sizeof(t_egg));
	if (memcpy(egg, tmp, sizeof(t_egg)) && (tmp = team->eggs))
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = egg;
	}
	else
		team->eggs = egg;
	return (egg->id);
}

int		hatch_egg(t_team *team, t_coord *pos)
{
	t_egg		*egg;
	t_egg		*tmp;
	int			egg_id;

	egg = team->eggs;
	*pos = egg->pos;
	team->eggs = egg->next;
	tmp = NULL;
	if ((egg = MAP(pos->x, pos->y).eggs))
		while (egg->next && egg->team_id != team->id && (tmp = egg))
			egg = egg->next;
	gfx_ebo_auto(egg);
	egg_id = egg->id;
	if (egg && egg->team_id == team->id && tmp)
		tmp->next = egg->next;
	else if (egg && egg->team_id == team->id)
		MAP(pos->x, pos->y).eggs = (egg) ? egg->next : NULL;
	else
		return (-1);
	free(egg);
	g_env.settings.num_eggs--;
	return (egg_id);
}

int		delete_egg(t_team *team)
{
	t_coord		pos;
	t_egg		*egg;
	t_egg		*tmp;
	int			id;

	egg = team->eggs;
	pos = egg->pos;
	id = egg->id;
	team->eggs = egg->next;
	tmp = NULL;
	if ((egg = MAP(pos.x, pos.y).eggs))
		while (egg->next && egg->team_id != team->id && (tmp = egg))
			egg = egg->next;
	if (egg && egg->team_id == team->id && tmp)
		tmp->next = egg->next;
	else if (egg && egg->team_id == team->id)
		MAP(pos.x, pos.y).eggs = (egg) ? egg->next : NULL;
	else
		return (-1);
	free(egg);
	g_env.settings.num_eggs--;
	return (id);
}

void	dec_egg_health(void)
{
	t_team		*team;
	t_egg		*egg;
	t_egg		*previous;

	team = g_env.settings.teams;
	while (team)
	{
		egg = team->eggs;
		previous = NULL;
		while (egg)
		{
			if (--egg->life <= 0)
			{
				gfx_edi_auto(delete_egg(team));
				egg = (previous) ? previous : team->eggs;
			}
			egg = (egg) ? egg->next : NULL;
		}
		team = team->next;
	}
}
