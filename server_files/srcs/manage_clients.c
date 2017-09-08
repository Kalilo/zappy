/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_clients.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 15:14:12 by khansman          #+#    #+#             */
/*   Updated: 2017/09/07 15:14:13 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

void	manage_clients(void)
{
	int			sd;
	t_client	*client;
	t_client	*previous;

	previous = NULL;
	client = g_env.clients;
	while (client)
	{
		sd = client->sock;
		if (FD_ISSET(sd, &READ_FDS) && client->num_commands < 10)
		{
			if (get_next_line(sd, &GNL_LINE) < 1 || !ft_strcmp(GNL_LINE, "quit\n"))
			{
				ft_putendl("Client disconnected...");
				close(sd);
				client = (previous) ? previous : g_env.clients;
				delete_client((previous) ? previous->next : g_env.clients);
			}
			else
				new_command(client, GNL_LINE);
			GNL_LINE = NULL;
		}
		previous = client;
		client = client->next;
	}
}
