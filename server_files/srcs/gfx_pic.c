/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_pic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 09:32:37 by khansman          #+#    #+#             */
/*   Updated: 2017/09/16 09:32:38 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

char	*gfx_pic_str(t_cli *cli, int level, t_coord pos)
{
	char	*str;
	char	*tmp;

	str = coord_to_str(pos);
	ft_str_append2("pic ", &str);
	ft_str_append(&str, " ");
	tmp = ft_itoa(level);
	str = ft_str_append3(&str, &tmp);
	while (cli)
	{
		if (cli->client)
		{
			tmp = ft_itoa(cli->client->id);
			ft_str_append(&str, " ");
			str = ft_str_append3(&str, &tmp);
		}
		cli = cli->next;
	}
	ft_str_append(&str, "\n");
	return (str);
}

void	gfx_pic_auto(t_coord pos, int level)
{
	char	*str;

	if (!g_env.gfx_cli)
		return ;
	str = gfx_pic_str(MAP(pos.x, pos.y).players, level, pos);
	send_gfx(str);
	ft_strdel(&str);
}
