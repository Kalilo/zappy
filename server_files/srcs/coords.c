/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coords.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 06:48:20 by khansman          #+#    #+#             */
/*   Updated: 2017/09/12 06:48:21 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

t_coord		move_coord(t_coord pos, t_direction direction)
{
	if (direction == north)
		pos.y++;
	else if (direction == east)
		pos.x++;
	else if (direction == south)
		pos.y--;
	else if (direction == west)
		pos.x--;
	else if (direction == north_west)
		MOVE_NW;
	else if (direction == north_east)
		MOVE_NE;
	else if (direction == south_east)
		MOVE_SE;
	else if (direction == south_west)
		MOVE_SW;
	return (pos);
}
