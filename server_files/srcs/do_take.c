/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_take.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 14:29:20 by khansman          #+#    #+#             */
/*   Updated: 2017/09/11 14:29:21 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

void	do_take(t_client *client, char *what)
{
	t_inventory		*inventory;
	int				id;

	inventory = &(MAP(client->pos.x, client->pos.y).inventory);
	if (!ft_strcmp(what, "linemate") && inventory->linemate)
		TAKE(linemate, 1);
	else if (!ft_strcmp(what, "deraumere") && inventory->deraumere)
		TAKE(deraumere, 2);
	else if (!ft_strcmp(what, "sibur") && inventory->sibur)
		TAKE(sibur, 3);
	else if (!ft_strcmp(what, "mendiane") && inventory->mendiane)
		TAKE(mendiane, 4);
	else if (!ft_strcmp(what, "phiras") && inventory->phiras)
		TAKE(phiras, 5);
	else if (!ft_strcmp(what, "thystame") && inventory->thystame)
		TAKE(thystame, 6);
	else if (!ft_strcmp(what, "food") && inventory->food)
		TAKE(food, 0);
	else
	{
		write_msg_to_sock(client->sock, "ko\n");
		return ;
	}
	write_msg_to_sock(client->sock, "ok\n");
	gfx_pgt_auto(client, id);
	add_random_gem(rand() % G_WIDTH, rand() % G_HEIGHT);
	client->delay -= 7;
}
