/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_sst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 16:35:52 by khansman          #+#    #+#             */
/*   Updated: 2017/09/15 16:35:53 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

void	gfx_sst(t_client *client, char *new_time)
{
	int		t;

	if ((t = ft_atoi(new_time)) < 1)
	{
		write_msg_to_sock(client->sock, "sbp\n");
		return ;
	}
	g_env.settings.fps = t;
	gfx_sgt(client);
}
