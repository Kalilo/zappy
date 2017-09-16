/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_pnw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 08:40:52 by khansman          #+#    #+#             */
/*   Updated: 2017/09/16 08:40:54 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

/*
** Automated send command
*/

char	*gfx_pnw_str(t_client *client)
{
	char	*str;
	char	*tmp;

	str = ft_itoa(client->id);
	ft_str_append2("pnw ", &str);
	ft_str_append(&str, " ");
	tmp = coord_to_str(client->pos);
	str = ft_str_append3(&str, &tmp);
	ft_str_append(&str, " ");
	tmp = ft_itoa((int)client->direction >> 1);
	str = ft_str_append3(&str, &tmp);
	ft_str_append(&str, " ");
	tmp = ft_itoa(client->level);
	str = ft_str_append3(&str, &tmp);
	ft_str_append(&str, find_client_team(client)->name);
	ft_str_append(&str, " ");
	return (str);
}

void	gfx_pnw(t_client *client)
{
	char	*str;

	if (!g_env.gfx_cli)
		return ;
	str = gfx_pnw_str(client);
	send_gfx(str);
	ft_strdel(&str);
}
