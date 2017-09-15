/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_pin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 16:24:28 by khansman          #+#    #+#             */
/*   Updated: 2017/09/15 16:24:29 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

char	*gfx_pin_str(t_client *player)
{
	char	*str;
	char	*tmp;

	str = ft_itoa(player->id);
	ft_str_append2("pin ", &str);
	ft_str_append(&str, " ");
	tmp = coord_to_str(player->pos);
	str = ft_str_append3(&str, &tmp);
	ft_str_append(&str, " ");
	tmp = inventory_to_str(&player->inventory);
	str = ft_str_append3(&str, &tmp);
	ft_str_append(&str, "\n");
	return (str);
}

void	gfx_pin(t_client *client, char *player_id)
{
	char		*str;
	t_client	*player;

	if (!(player = find_client_by_id(ft_atoi(player_id))))
	{
		write_msg_to_sock(client->sock, "sbp\n");
		return ;
	}
	str = gfx_pin_str(player);
	write_msg_to_sock(client->sock, str);
	ft_strdel(&str);
}
