/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_mct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 14:55:52 by khansman          #+#    #+#             */
/*   Updated: 2017/09/15 14:55:53 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

void	gfx_mct(t_client *client)
{
	unsigned int	k;
	unsigned int	l;
	char			*str;

	k = 0;
	while (k < G_WIDTH)
	{
		l = 0;
		while (l < G_HEIGHT)
		{
			str = gfx_bct_str((t_coord){k, l});
			write_msg_to_sock(client->sock, str);
			ft_strdel(&str);
			l++;
		}
		k++;
	}
}
