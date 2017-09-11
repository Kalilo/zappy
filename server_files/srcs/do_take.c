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

	inventory = &(MAP(client->pos_x, client->pos_y).inventory);
	if (!ft_strcmp(what, "linemate") && inventory->linemate)
		TAKE(linemate);
	else if (!ft_strcmp(what, "deraumere") && inventory->deraumere)
		TAKE(deraumere);
	else if (!ft_strcmp(what, "sibur") && inventory->sibur)
		TAKE(sibur);
	else if (!ft_strcmp(what, "mendiane") && inventory->mendiane)
		TAKE(mendiane);
	else if (!ft_strcmp(what, "phiras") && inventory->phiras)
		TAKE(phiras);
	else if (!ft_strcmp(what, "thystame") && inventory->thystame)
		TAKE(thystame);
	else if (!ft_strcmp(what, "food") && inventory->food)
		TAKE(food);
	else
	{
		write_msg_to_sock(client->sock, "ko\n");
		return ;
	}
	write_msg_to_sock(client->sock, "ok\n");
	add_random_gem(rand() % G_WIDTH, rand() % G_HEIGHT);
	client->delay -= 7;
}
