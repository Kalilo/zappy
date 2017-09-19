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
		pos.y--;
	else if (direction == east)
		pos.x++;
	else if (direction == south)
		pos.y++;
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

char		*coord_to_str(t_coord coord)
{
	char	*str;
	char	*x;
	char	*y;
	int		len;
	int		tmp;

	x = ft_itoa(coord.x);
	y = ft_itoa(coord.y);
	tmp = ft_strlen(x);
	len = tmp + ft_strlen(y) + 2;
	if (!(str = (char *)malloc(len)))
		error_quit("Insufficient memory");
	ft_memcpy(str, x, tmp);
	str[tmp++] = ' ';
	ft_memcpy(&str[tmp], y, ft_strlen(y));
	str[len - 1] = '\0';
	free(x);
	free(y);
	return (str);
}
