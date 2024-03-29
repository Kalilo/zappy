/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_ppo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 14:41:56 by khansman          #+#    #+#             */
/*   Updated: 2017/09/27 14:41:57 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

char	*gfx_ppo_str(t_client *player)
{
	char	*str;
	char	*tmp;

	str = ft_itoa(player->id);
	ft_str_append2("ppo ", &str);
	ft_str_append(&str, " ");
	tmp = coord_to_str(player->pos);
	str = ft_str_append3(&str, &tmp);
	ft_str_append(&str, " ");
	tmp = ft_itoa(((int)player->direction >> 1) + 1);
	str = ft_str_append3(&str, &tmp);
	ft_str_append(&str, "\n");
	return (str);
}

void	gfx_ppo(t_client *client, char *player_id)
{
	t_client	*player;
	char		*str;

	if (!(player = find_client_by_id(ft_atoi(player_id))))
	{
		write_msg_to_sock(client->sock, "sbp\n");
		return ;
	}
	str = gfx_ppo_str(player);
	write_msg_to_sock(client->sock, str);
	ft_strdel(&str);
}

void	gfx_ppo_auto(t_client *client)
{
	char	*str;

	if (!g_env.gfx_cli)
		return ;
	str = gfx_ppo_str(client);
	send_gfx(str);
	ft_strdel(&str);
}
