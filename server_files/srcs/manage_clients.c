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

void		manaage_client_loop(int sd,  t_client *start, t_client *client, \
	t_client *previous, char gfx)
{
	while (client)
	{
		sd = client->sock;
		if (FD_ISSET(sd, &READ_FDS) && client->num_commands < 10)
		{
			if (get_next_line(sd, &GNL_LINE) < 1 || \
				!ft_strcmp(GNL_LINE, "quit"))
			{
				ft_putendl("Client disconnected...");
				close(sd);
				client = (previous) ? previous : start;
				if (!gfx)
					delete_client((previous) ? previous->next : start);
				else
					delete_gfx_client((previous) ? previous->next : start);
			}
			else if (!ft_strcmp(GNL_LINE, "GRAPHIC"))
			{
				join_gfx(client);
				client = (previous) ? previous : start;
			}
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
	int			sd;
	t_client	*previous;

	previous = NULL;
	sd = 0;
	manaage_client_loop(sd, g_env.clients, g_env.clients, previous, 0);
	manaage_client_loop(sd, g_env.gfx_cli, g_env.gfx_cli, previous, 1);
}
