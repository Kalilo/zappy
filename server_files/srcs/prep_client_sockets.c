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

void	prep_client_sockets(void)
{
	int			sd;
	t_client	*client;

	FD_ZERO(&READ_FDS);
	FD_SET(MASTER_SOCK, &READ_FDS);
	client = g_env.clients;
	while (client)
	{
		sd = client->sock;
		if (sd > MASTER_MAX_SD)
			MASTER_MAX_SD = sd;
		FD_SET(sd, &READ_FDS);
	}
}
