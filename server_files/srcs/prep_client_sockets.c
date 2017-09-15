/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_client_sockets.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 14:44:55 by khansman          #+#    #+#             */
/*   Updated: 2017/09/07 14:44:58 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

static void	prep_client_lst(t_client *client)
{
	int			sd;

	while (client)
	{
		sd = client->sock;
		if (sd < 1)
			continue ;
		if (sd > MASTER_MAX_SD)
			MASTER_MAX_SD = sd;
		FD_SET(sd, &READ_FDS);
		client = client->next;
	}
}

void		prep_client_sockets(void)
{
	FD_ZERO(&READ_FDS);
	FD_SET(MASTER_SOCK, &READ_FDS);
	MASTER_MAX_SD = MASTER_SOCK;
	prep_client_lst(g_env.clients);
	prep_client_lst(g_env.gfx_cli);
}
