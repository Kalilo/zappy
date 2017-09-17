/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_tna.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 14:59:59 by khansman          #+#    #+#             */
/*   Updated: 2017/09/15 15:00:00 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

void	gfx_tna(t_client *client)
{
	char	*str;
	t_team	*team;

	team = g_env.settings.teams;
	while (team)
	{
		str = ft_strdup(team->name);
		ft_str_append2("tna ", &str);
		ft_str_append(&str, "\n");
		write_msg_to_sock(client->sock, str);
		ft_strdel(&str);
		team = team->next;
	}
}
