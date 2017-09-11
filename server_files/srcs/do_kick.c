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

	k = MAP(client->pos_x, client->pos_y).players;
	kicked = 0;
	while (k)
	{
		if (k->client != client && kicked == 1)
		{
			send_moving_msg(k->client->sock, client->direction);
			move_cli(k->client, client->direction);
			k =  MAP(client->pos_x, client->pos_y).players;//temp fix
		}
		else//temp fix
			k = k->next;
	}
	if (kicked)
		write_msg_to_sock(client->sock, "ok\n");
	else
		write_msg_to_sock(client->sock, "ko\n");
	client->delay -= 7;
}
