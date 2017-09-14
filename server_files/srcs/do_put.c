/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 15:07:55 by khansman          #+#    #+#             */
/*   Updated: 2017/09/11 15:07:56 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

void	do_put(t_client *client, char *what)
{
	t_inventory		*inventory;

	inventory = &(MAP(client->pos.x, client->pos.y).inventory);
	if (!ft_strcmp(what, "linemate") && client->inventory.linemate)
		PUT(linemate);
	else if (!ft_strcmp(what, "deraumere") && client->inventory.deraumere)
		PUT(deraumere);
	else if (!ft_strcmp(what, "sibur") && client->inventory.sibur)
		PUT(sibur);
	else if (!ft_strcmp(what, "mendiane") && client->inventory.mendiane)
		PUT(mendiane);
	else if (!ft_strcmp(what, "phiras") && client->inventory.phiras)
		PUT(phiras);
	else if (!ft_strcmp(what, "thystame") && client->inventory.thystame)
		PUT(thystame);
	else if (!ft_strcmp(what, "food") && client->inventory.food)
		PUT(food);
	else
	{
		write_msg_to_sock(client->sock, "ko\n");
		return ;
	}
	write_msg_to_sock(client->sock, "ok\n");
	client->delay -= 7;
}

