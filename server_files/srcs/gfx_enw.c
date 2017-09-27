/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_enw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 14:39:53 by khansman          #+#    #+#             */
/*   Updated: 2017/09/27 14:39:54 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

char	*gfx_enw_str(t_client *client, int egg_id)
{
	char	*str;
	char	*tmp;

	str = ft_itoa(egg_id);
	ft_str_append2("enw ", &str);
	ft_str_append(&str, " ");
	tmp = ft_itoa(client->id);
	str = ft_str_append3(&str, &tmp);
	ft_str_append(&str, " ");
	tmp = coord_to_str(client->pos);
	str = ft_str_append3(&str, &tmp);
	ft_str_append(&str, "\n");
	return (str);
}

void	gfx_enw_auto(t_client *client, int egg_id)
{
	char	*str;

	if (!g_env.gfx_cli)
		return ;
	str = gfx_enw_str(client, egg_id);
	send_gfx(str);
	ft_strdel(&str);
}
