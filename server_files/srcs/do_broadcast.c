/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_broadcast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 06:53:06 by khansman          #+#    #+#             */
/*   Updated: 2017/09/13 06:53:07 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

t_direction	incomming_direction(t_coord src, t_coord dest)
{
	float		delta_x;
	float		delta_y;

	delta_x = (dest.x - src.x);
	delta_y = (dest.y - src.y);
	if (fabs(delta_x) == fabs(delta_y))
	{
		if (delta_x > 0 && delta_y > 0)
			return (north_east);
		else if (delta_x > 0 && delta_y < 0)
			return (south_east);
		else if (delta_x < 0 && delta_y > 0)
			return (north_west);
		else if (delta_x < 0 && delta_y < 0)
			return (south_west);
	}
	if (fabs(delta_x) > fabs(delta_y))
		return ((delta_x > 0) ? east : west);
	return ((delta_y > 0) ? north : south);
}

t_coord		closest_coord(t_coord src, t_coord dest)
{
	t_coord		closest;
	float		shortest_dist;
	float		tmp;

	closest = dest;
	shortest_dist = ft_dist(src, dest);
	if (IS_CLOSER(((t_coord){dest.x - G_WIDTH, dest.y - G_HEIGHT})))
		CLOSEST_CLI = (t_coord){dest.x - G_WIDTH, dest.y - G_HEIGHT};
	if (IS_CLOSER(((t_coord){dest.x, dest.y - G_HEIGHT})))
		CLOSEST_CLI = (t_coord){dest.x, dest.y - G_HEIGHT};
	if (IS_CLOSER(((t_coord){dest.x + G_WIDTH, dest.y - G_HEIGHT})))
		CLOSEST_CLI = (t_coord){dest.x + G_WIDTH, dest.y - G_HEIGHT};
	if (IS_CLOSER(((t_coord){dest.x - G_WIDTH, dest.y})))
		CLOSEST_CLI = (t_coord){dest.x - G_WIDTH, dest.y};
	if (IS_CLOSER(((t_coord){dest.x + G_WIDTH, dest.y})))
		CLOSEST_CLI = (t_coord){dest.x + G_WIDTH, dest.y};
	if (IS_CLOSER(((t_coord){dest.x - G_WIDTH, dest.y + G_HEIGHT})))
		CLOSEST_CLI = (t_coord){dest.x - G_WIDTH, dest.y + G_HEIGHT};
	if (IS_CLOSER(((t_coord){dest.x, dest.y + G_HEIGHT})))
		CLOSEST_CLI = (t_coord){dest.x, dest.y + G_HEIGHT};
	if (IS_CLOSER(((t_coord){dest.x + G_WIDTH, dest.y + G_HEIGHT})))
		CLOSEST_CLI = (t_coord){dest.x + G_WIDTH, dest.y + G_HEIGHT};
	return (closest);
}

void		send_msg(t_client *client, char *msg)
{
	t_client	*cli;
	char		*str;
	t_coord		closest;

	cli = g_env.clients;
	while (cli)
	{
		if (cli == client)
		{
			str = ft_strdup(msg);
			ft_str_append2("message 0, ", &str);
		}
		else
		{
			closest = closest_coord(CLI_POS, cli->pos);
			str = ft_itoa((int)dec_dir(incomming_direction(CLI_POS, closest), \
				north_diff(cli->direction)));
			ft_str_append2("message ", &str);
			ft_str_append(&str, ", ");
			ft_str_append(&str, msg);
		}
		ft_str_append(&str, "\n");
		write_msg_to_sock(cli->sock, str);
		ft_strdel(&str);
		cli = cli->next;
	}
}

void		do_bradcast(t_client *client, char *msg)
{
	send_msg(client, msg);
	gfx_pbc_auto(client, msg);
	client->delay -= 7;
}
