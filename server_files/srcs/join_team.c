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
	if (!team || (t->avaliable_cons < 1))
		return (0);
	if (t->eggs)
	{
		//
	}
	else
	{
		//
	}
	return (1);
}
