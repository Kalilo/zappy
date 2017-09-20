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

void		handle_command(t_client *client, char *line)
{
	if (!valid_command(line) && client->level)
		write_msg_to_sock(client->sock, "error\n");
	else
		new_command(client, line);
}

void		manaage_client_loop(t_client *start, t_client *client, \
	t_client *previous, char gfx)
{
	while (client)
	{
		if (FD_ISSET(client->sock, &READ_FDS) && client->num_commands < 10)
		{
			if (get_next_line(client->sock, &GNL_LINE) < 1 || \
				!ft_strcmp(GNL_LINE, "quit"))
			{
				ft_putendl("Client disconnected...");
				close(client->sock);
				client = (previous) ? previous : start;
				if (gfx == 0)
					delete_client((previous) ? previous->next : start);
				else
					delete_gfx_client((previous) ? previous->next : start);
			}
			else if (make_gfx_cli(client))
				client = (previous) ? previous : start;
			else
				handle_command(client, GNL_LINE);
			GNL_LINE = NULL;
		}
		previous = client;
		client = client->next;
	}
}

void		manage_clients(void)
{
	t_client	*previous;

	previous = NULL;
	manaage_client_loop(g_env.clients, g_env.clients, previous, 0);
	manaage_client_loop(g_env.gfx_cli, g_env.gfx_cli, previous, 1);
}
