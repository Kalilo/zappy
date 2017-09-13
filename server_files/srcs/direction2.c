/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 07:14:36 by khansman          #+#    #+#             */
/*   Updated: 2017/09/12 07:14:37 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

t_direction	inc_dir(t_direction dir, int amount)
{
	while (amount-- > 0)
	{
		if (dir == north)
			dir = north_east;
		else if (dir == north_east)
			dir = east;
		else if (dir == east)
			dir = south_east;
		else if (dir == south_east)
			dir = south;
		else if (dir == south)
			dir = south_west;
		else if (dir == south_west)
			dir = west;
		else if (dir == west)
			dir = north_west;
		else if (dir == north_west)
			dir = north;
	}
	return (dir);
}

t_direction	dec_dir(t_direction dir, int amount)
{
	while (amount-- > 0)
	{
		if (dir == north)
			dir = north_west;
		else if (dir == north_east)
			dir = north;
		else if (dir == east)
			dir = north_east;
		else if (dir == south_east)
			dir = east;
		else if (dir == south)
			dir = south_east;
		else if (dir == south_west)
			dir = south;
		else if (dir == west)
			dir = south_west;
		else if (dir == north_west)
			dir = west;
	}
	return (dir);
}

int			north_diff(t_direction dir)
{
	return ((int)dir);
}
