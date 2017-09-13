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

float		ft_dist(t_coord a, t_coord b)
{
	return (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
}

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
	return ()
}

t_coord		closest_coord(t_coord src, t_coord dest)
{
	t_coord		closest;
	float		shortest_dist;
	float		tmp;

	closest = dest;
	shortest_dist = ft_dist(src, dest);
	if ((tmp = ft_dist(src, (t_coord){dest.x - G_WIDTH, dest.y - G_HEIGHT})) < shortest_dist)
		shortest_dist = tmp, closest = (t_coord){dest.x - G_WIDTH, dest.y - G_HEIGHT};
	if ((tmp = ft_dist(src, (t_coord){dest.x, dest.y - G_HEIGHT})) < shortest_dist)
		shortest_dist = tmp, closest = (t_coord){dest.x, dest.y - G_HEIGHT};
	if ((tmp = ft_dist(src, (t_coord){dest.x + G_WIDTH, dest.y - G_HEIGHT})) < shortest_dist)
		shortest_dist = tmp, closest = (t_coord){dest.x + G_WIDTH, dest.y - G_HEIGHT};
	if ((tmp = ft_dist(src, (t_coord){dest.x - G_WIDTH, dest.y})) < shortest_dist)
		shortest_dist = tmp, closest = (t_coord){dest.x - G_WIDTH, dest.y};
	if ((tmp = ft_dist(src, (t_coord){dest.x + G_WIDTH, dest.y})) < shortest_dist)
		shortest_dist = tmp, closest = (t_coord){dest.x + G_WIDTH, dest.y};
	if ((tmp = ft_dist(src, (t_coord){dest.x - G_WIDTH, dest.y + G_HEIGHT})) < shortest_dist)
		shortest_dist = tmp, closest = (t_coord){dest.x - G_WIDTH, dest.y + G_HEIGHT};
	if ((tmp = ft_dist(src, (t_coord){dest.x, dest.y + G_HEIGHT})) < shortest_dist)
		shortest_dist = tmp, closest = (t_coord){dest.x, dest.y + G_HEIGHT};
	if ((tmp = ft_dist(src, (t_coord){dest.x + G_WIDTH, dest.y + G_HEIGHT})) < shortest_dist)
		shortest_dist = tmp, closest = (t_coord){dest.x + G_WIDTH, dest.y + G_HEIGHT};
	return (closest);
}

void		do_bradcast(t_client *client, char *msg)
{
	// calculate shortest distance
	// run line plot between two squares, and return final square before dest
	// calculate which number the square is
	// assemble the message
	// write message to sock
	// free message
	// decrease delay.
}
