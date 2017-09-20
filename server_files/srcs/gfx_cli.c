/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_cli.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 13:22:05 by khansman          #+#    #+#             */
/*   Updated: 2017/09/15 13:22:08 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

t_client	*new_gfx_client(unsigned int sock)
{
	t_client	*client;
	t_client	*lst;

	if (!(client = (t_client *)ft_strnew(sizeof(t_client))))
		error_quit("Insufficient memory avaliable.");
	client->sock = sock;
	if (!g_env.gfx_cli)
		g_env.gfx_cli = client;
	else
	{
		lst = g_env.gfx_cli;
		while (lst->next)
			lst = lst->next;
		lst->next = client;
	}
	return (client);
}

void		welcome_gfx(t_client *client)
{
	gfx_msz(client);
	gfx_sgt(client);
	gfx_mct(client);
	gfx_tna(client);
}

char		join_gfx(t_client *client)
{
	t_client	*new_gfx;

	new_gfx = new_gfx_client(client->sock);
	new_gfx->command = client->command;
	delete_client(client);
	welcome_gfx(new_gfx);
	return (1);
}

void		send_gfx(char *str)
{
	t_client	*client;

	client = g_env.gfx_cli;
	while (client)
	{
		write_msg_to_sock(client->sock, str);
		client = client->next;
	}
}

char		make_gfx_cli(t_client *client)
{
	if (!ft_strcmp(GNL_LINE, "GRAPHIC"))
	{
		join_gfx(client);
		return (1);
	}
	return (0);
}
