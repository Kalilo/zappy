/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_kick.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 14:11:10 by khansman          #+#    #+#             */
/*   Updated: 2017/09/11 14:11:16 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

void	send_moving_msg(int sock, t_direction direction)
{
	if (direction == north)
		write_msg_to_sock(sock, "moving north\n");
	else if (direction == east)
		write_msg_to_sock(sock, "moving east\n");
	else if (direction == south)
		write_msg_to_sock(sock, "moving south\n");
	else if (direction == west)
		write_msg_to_sock(sock, "moving west\n");
}

void	do_kick(t_client *client)
{
	t_cli	*k;
	char	kicked;

	k = MAP(client->pos.x, client->pos.y).players;
	kicked = 0;
	gfx_pex_auto(client);
	while (k)
	{
		if (k->client->id != client->id && (kicked = 1))
		{
			send_moving_msg(k->client->sock, client->direction);
			move_cli(k->client, client->direction);
			gfx_ppo_auto(k->client);
		}
		k = k->next;
	}
	if (kicked)
		write_msg_to_sock(client->sock, "ok\n");
	else
		write_msg_to_sock(client->sock, "ko\n");
	client->delay -= 7;
}
