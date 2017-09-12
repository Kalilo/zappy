/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 09:47:04 by khansman          #+#    #+#             */
/*   Updated: 2017/09/09 09:47:06 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

void	add_random_gem(int x, int y)
{
	int				type;

	type = rand() % 100;
	if (type < 20)
		(MAP(x, y).inventory.linemate)++;
	else if (type < 40)
		(MAP(x, y).inventory.deraumere)++;
	else if (type < 60)
		(MAP(x, y).inventory.sibur)++;
	else if (type < 75)
		(MAP(x, y).inventory.mendiane)++;
	else if (type < 90)
		(MAP(x, y).inventory.phiras)++;
	else
		(MAP(x, y).inventory.thystame)++;
}

void	populate_map(void)
{
	unsigned int	k;
	unsigned int	l;
	unsigned int	max;

	k = 0;
	while (k < G_WIDTH)
	{
		l = 0;
		max = 0;
		while (l < G_HEIGHT)
		{
			while (rand() % 100 > 40 && max < 20)
				add_random_gem(k, l);
			l++;
		}
		k++;
	}
}
