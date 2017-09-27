/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_bct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 14:29:19 by khansman          #+#    #+#             */
/*   Updated: 2017/09/15 14:29:21 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

char	*gfx_bct_str(t_coord pos)
{
	char	*str;
	char	*tmp;

	str = coord_to_str(pos);
	ft_str_append2("bct ", &str);
	ft_str_append(&str, " ");
	tmp = inventory_to_str(&(MAP(pos.x, pos.y).inventory));
	str = ft_str_append3(&str, &tmp);
	ft_str_append(&str, "\n");
	return (str);
}

void	gfx_bct(t_client *client, char *params)
{
	t_coord	pos;
	char	*str;

	if (!(str = ft_strchr(params, ' ')) || str != ft_strrchr(params, ' ') ||
			!*(++str))
	{
		write_msg_to_sock(client->sock, "sbp\n");
		return ;
	}
	pos.x = ft_atoi(params);
	pos.y = ft_atoi(str);
	str = gfx_bct_str(pos);
	write_msg_to_sock(client->sock, str);
	ft_strdel(&str);
}

void	gfx_bct_auto(t_coord pos)
{
	char	*str;

	if (!(g_env.gfx_cli))
		return ;
	str = gfx_bct_str(pos);
	send_gfx(str);
	ft_strdel(&str);
}
