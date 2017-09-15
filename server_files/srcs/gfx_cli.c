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

char		join_gfx(t_client *client)
{
	t_client	*new_gfx;

	new_gfx = new_gfx_client(client->sock);
	new_gfx->command = client->command;
	delete_client(client);
	return (1);
}
