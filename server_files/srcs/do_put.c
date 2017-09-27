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

static void	do_put_2(t_client *client, int id)
{
	write_msg_to_sock(client->sock, "ok\n");
	gfx_pdr_auto(client, id);
	gfx_pin_auto(client);
	gfx_bct_auto(client->pos);
	client->delay -= 7;
}

void		do_put(t_client *client, char *what)
{
	t_inventory		*inventory;
	int				id;

	inventory = &(MAP(client->pos.x, client->pos.y).inventory);
	if (!ft_strcmp(what, "linemate") && client->inventory.linemate)
		PUT(linemate, 1);
	else if (!ft_strcmp(what, "deraumere") && client->inventory.deraumere)
		PUT(deraumere, 2);
	else if (!ft_strcmp(what, "sibur") && client->inventory.sibur)
		PUT(sibur, 3);
	else if (!ft_strcmp(what, "mendiane") && client->inventory.mendiane)
		PUT(mendiane, 4);
	else if (!ft_strcmp(what, "phiras") && client->inventory.phiras)
		PUT(phiras, 5);
	else if (!ft_strcmp(what, "thystame") && client->inventory.thystame)
		PUT(thystame, 6);
	else if (!ft_strcmp(what, "food") && client->inventory.food)
		PUT(food, 0);
	else
	{
		write_msg_to_sock(client->sock, "ko\n");
		return ;
	}
	do_put_2(client, id);
}
