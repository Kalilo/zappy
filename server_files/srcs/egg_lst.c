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

void	lay_egg(t_client *client)
{
	t_egg	*egg;
	t_egg	*tmp;
	t_team	*team;

	egg = MAP(client->pos.x, client->pos.y).eggs;
	while (egg && egg->next)
		egg = egg->next;
	tmp = (t_egg *)ft_strnew(sizeof(t_egg));
	tmp->team_id = client->team_id;
	tmp->pos = (t_coord){client->pos.x, client->pos.y};
	if (egg)
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
}

t_coord	hatch_egg(t_team *team)
{
	t_coord	pos;
	t_egg	*egg;
	t_egg	*tmp;

	egg = team->eggs;
	pos = egg->pos;
	team->eggs = egg->next;
	free(egg);
	tmp = NULL;
	if ((egg = MAP(pos.x, pos.y).eggs))
		while (egg->next && egg->team_id != team->id && (tmp = egg))
			egg = egg->next;
	if (egg && egg->team_id == team->id && tmp)
	{
		tmp->next = egg->next;
		free(egg);
	}
	else if (egg && egg->team_id == team->id)
	{
		MAP(pos.x, pos.y).eggs = (egg) ? egg->next : NULL;
		free(egg);
	}
	return (pos);
}
