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

char	*sum_tile_content(t_tile *tile)
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
		ft_str_append(&str, " player");
	return (str);
}

/*
** Need to rewrite usiing direction to update the position
** Current method can't account for wrapping around the edge
*/
char	*sum_range(int x_min, int y_min, int x_max, int y_max)
{
	char	*str;
	char	*tmp;

	str = sum_tile_content(&MAP(x_min, y_min));
	while (1)
	{
		if (x_min == x_max && y_min == y_max)
			break ;
		else if (x_min < x_max)
			x_min++;
		else if (x_min > x_max)
			x_min--;
		else if (y_min < y_max)
			y_min++;
		else if (y_min > y_max)
			y_min--;
		ft_str_append(&str, ", ");
		tmp = sum_tile_content(&MAP(x_min, y_min));
		str = ft_str_append3(&str, &tmp);
	}
	return (str);
}

char	*get_in_sight(t_client *client)
{
	int		level;
	char	*str;
	char	*tmp;

	level = client->level;
	str = ft_strdup("{");
	while (level-- >= 0)
	{
		//
	}
	ft_str_append(&str, "}");
	return (str);
}
