/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 11:23:18 by khansman          #+#    #+#             */
/*   Updated: 2017/09/09 11:23:19 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

t_cli	*new_cli(t_tile *tile)
{
	t_cli		*cli;
	t_cli		*previous;

	if (!(cli = (t_cli *)ft_strnew(sizeof(t_cli))))
		error_quit("Insufficient memory avaliable.");
	if (!tile->players)
		tile->players = cli;
	else
	{
		previous = tile->players;
		while (previous->next)
			previous = previous->next;
		previous->next = cli;
	}
	return (cli);
}

void	delete_cli(t_tile *tile, t_client *client)
{
	t_cli		*tmp;
	t_cli		*previous;

	if (!(previous = tile->players))
		return ;
	if (previous->client == client)
	{
		tile->players = previous->next;
		free(previous);
	}
	else
	{
		tmp = previous->next;
		while (tmp && tmp->client != client)
		{
			previous = tmp;
			tmp = tmp->next;
		}
		if (!tmp)
			return ;
		previous->next = tmp->next;
		free(tmp);
	}
}

void	move_cli(t_client *client, t_direction direction)
{
	delete_cli(&MAP(client->pos.x, client->pos.y), client);
	if (direction == north)
		client->pos.y = (client->pos.y == 0) ? (int)G_WIDTH - 1 : \
			client->pos.y - 1;
	else if (direction == east)
		client->pos.x = ((int)G_WIDTH - 1 == client->pos.x) ? \
			0 : client->pos.x + 1;
	else if (direction == south)
		client->pos.y = ((int)G_WIDTH - 1 == client->pos.y) ? \
			0 : client->pos.y + 1;
	else if (direction == west)
		client->pos.x = (client->pos.x == 0) ? (int)G_WIDTH - 1 : \
			client->pos.x - 1;
	new_cli(&MAP(client->pos.x, client->pos.y));
}
