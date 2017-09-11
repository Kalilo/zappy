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
