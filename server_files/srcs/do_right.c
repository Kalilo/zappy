/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_right.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 14:09:38 by khansman          #+#    #+#             */
/*   Updated: 2017/09/09 14:09:40 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

void	do_right(t_client *client)
{
	if (client->direction == north)
		client->direction = east;
	else if (client->direction == east)
		client->direction = south;
	else if (client->direction == south)
		client->direction = west;
	else if (client->direction == west)
		client->direction = north;
	write_msg_to_sock(client->sock, "ok\n");
	gfx_ppo_auto(client);
	client->delay -= 7;
}
