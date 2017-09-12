/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 07:14:36 by khansman          #+#    #+#             */
/*   Updated: 2017/09/12 07:14:37 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

t_direction opposite_direction(t_direction direction)
{
	if (direction == north)
		return (south);
	else if (direction == east)
		return (west);
	else if (direction == south)
		return (north);
	else if (direction == west)
		return (east);
	else if (direction == north_west)
		return (south_east);
	else if (direction == north_east)
		return (south_west);
	else if (direction == south_east)
		return (north_west);
	else if (direction == south_west)
		return (north_east);
	return (no_direction);
}

t_direction tangent_right_direction(t_direction direction)
{
	if (direction == north)
		return (east);
	else if (direction == east)
		return (south);
	else if (direction == south)
		return (west);
	else if (direction == west)
		return (north);
	else if (direction == north_west)
		return (north_east);
	else if (direction == north_east)
		return (south_east);
	else if (direction == south_east)
		return (south_west);
	else if (direction == south_west)
		return (north_west);
	return (no_direction);
}

t_direction tangent_left_direction(t_direction direction)
{
	if (direction == north)
		return (west);
	else if (direction == east)
		return (north);
	else if (direction == south)
		return (east);
	else if (direction == west)
		return (south);
	else if (direction == north_west)
		return (south_west);
	else if (direction == north_east)
		return (north_west);
	else if (direction == south_east)
		return (north_east);
	else if (direction == south_west)
		return (south_east);
	return (no_direction);
}

t_direction adjacent_right_direction(t_direction direction)
{
	if (direction == north)
		return (north_east);
	else if (direction == east)
		return (south_east);
	else if (direction == south)
		return (south_west);
	else if (direction == west)
		return (north_west);
	else if (direction == north_west)
		return (north);
	else if (direction == north_east)
		return (east);
	else if (direction == south_east)
		return (south);
	else if (direction == south_west)
		return (west);
	return (no_direction);
}

t_direction adjacent_left_direction(t_direction direction)
{
	if (direction == north)
		return (north_west);
	else if (direction == east)
		return (north_east);
	else if (direction == south)
		return (south_east);
	else if (direction == west)
		return (south_west);
	else if (direction == north_west)
		return (west);
	else if (direction == north_east)
		return (north);
	else if (direction == south_east)
		return (east);
	else if (direction == south_west)
		return (south);
	return (no_direction);
}
