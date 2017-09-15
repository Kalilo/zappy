/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_plv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 16:18:15 by khansman          #+#    #+#             */
/*   Updated: 2017/09/15 16:18:16 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

char	*gfx_plv_str(t_client *player)
{
	char		*str;
	char		*tmp;

	str = ft_itoa(player->id);
	ft_str_append2(" plv", &str);
	ft_str_append(&str, " ");
	tmp = ft_itoa(player->level);
	str = ft_str_append3(&str, &tmp);
	ft_str_append(&str, "\n");
	return (str);
}

void	gfx_plv(t_client *client, char *player_id)
{
	char		*str;
	t_client	*player;

	if (!(player = find_client_by_id(ft_atoi(player_id))))
	{
		write_msg_to_sock(client->sock, "sbp\n");
		return ;
	}
	str = gfx_plv_str(player);
	write_msg_to_sock(client->sock, str);
	ft_strdel(&str);
}
