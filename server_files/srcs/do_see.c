/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_see.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 14:09:54 by khansman          #+#    #+#             */
/*   Updated: 2017/09/09 14:09:55 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

/*
** these functions aren't very effient, though should serve their purpose
*/
char	*sum_tile_content(t_tile *tile, t_client *client)
{
	char	*str;
	int		k;
	t_cli	*cli;

	str = ft_strdup("");
	k = tile->inventory.linemate;
	REP_APPEND(" linemate");
	k = tile->inventory.deraumere;
	REP_APPEND(" deraumere");
	k = tile->inventory.sibur;
	REP_APPEND(" sibur");
	k = tile->inventory.mendiane;
	REP_APPEND(" mendiane");
	k = tile->inventory.phiras;
	REP_APPEND(" phiras");
	k = tile->inventory.thystame;
	REP_APPEND(" thystame");
	k = tile->inventory.food;
	REP_APPEND(" food");
	cli = tile->players;
	while (cli && ((cli = cli->next) || 1))
		if (cli->client != client)
			ft_str_append(&str, " player");
	return (str);
}

char	*sum_range(t_coord min, t_coord max, t_direction dir, t_client *client)
{
	char	*str;
	char	*tmp;

	str = sum_tile_content(&MAP(min.x % G_WIDTH, min.y % G_HEIGHT), client);
	while (1)
	{
		if (min.x == max.x && min.y == max.y)
			break ;
		else
			min = move_coord(min, dir);
		ft_str_append(&str, ",");
		tmp = sum_tile_content(&MAP(min.x % G_WIDTH, min.y %G_HEIGHT), client);
		str = ft_str_append3(&str, &tmp);
	}
	return (str);
}

char	*get_in_sight(t_client *client)
{
	int		level;
	char	*str;
	char	*tmp;
	t_coord	min;
	t_coord	max;

	level = client->level;
	min = max = (t_coord){client->pos_x, client->pos_y};
	str = sum_range(min, max, tangent_right_direction(client->direction),
		client);
	ft_str_append2("{", &str);
	while (--level >= 0)
	{
		ft_str_append(&str, ",");
		min = move_coord(min, client->direction);
		max = move_coord(max, client->direction);
		min = move_coord(min, tangent_left_direction(client->direction));
		max = move_coord(max, tangent_right_direction(client->direction));
		tmp = sum_range(min, max, tangent_right_direction(client->direction),
			client);
		str = ft_str_append3(&str, &tmp);
	}
	ft_str_append(&str, "}\n");
	return (str);
}

void	do_see(t_client *client)
{
	char	*str;

	str = get_in_sight(client);
	write_msg_to_sock(client->sock, str);
	ft_strdel(&str);
	client->delay -= 7;
}
