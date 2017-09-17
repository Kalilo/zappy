/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_enw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 11:13:23 by khansman          #+#    #+#             */
/*   Updated: 2017/09/16 11:13:23 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

char	*gfx_enw_str(t_client *client)
{
	char	*str;
	char	*tmp;

	str = ft_itoa(g_env.settings.num_eggs);
	ft_str_append2("enw ", &str);
	ft_str_append(&str, " ");
	tmp = ft_itoa(client->id);
	str = ft_str_append3(&str, &tmp);
	ft_str_append(&str, " ");
	tmp = coord_to_str(client->pos);
	ft_str_append(&str, "\n");
	return (str);
}

void	gfx_enw_auto(t_client *client)
{
	char	*str;

	if (!g_env.gfx_cli)
		return ;
	str = gfx_enw_str(client);
	send_gfx(str);
	ft_strdel(&str);
}