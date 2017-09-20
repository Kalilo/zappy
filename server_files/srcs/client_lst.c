/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 11:08:00 by khansman          #+#    #+#             */
/*   Updated: 2017/09/07 11:08:01 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

t_client	*new_client(unsigned int sock)
{
	t_client	*client;
	t_client	*lst;

	if (!(client = (t_client *)ft_strnew(sizeof(t_client))))
		error_quit("Insufficient memory avaliable.");
	client->sock = sock;
	if (!g_env.clients)
		g_env.clients = client;
	else
	{
		lst = g_env.clients;
		while (lst->next)
			lst = lst->next;
		lst->next = client;
	}
	return (client);
}

void		delete_client(t_client *client)
{
	t_client	*previous;

	if (!client)
		return ;
	if (client->level > 0 && (num_clients_in_team(client->team_id) < \
			(g_env.settings.num_start_clients / g_env.settings.num_teams)))
		find_client_team(client)->avaliable_cons++;
	if (client->level > 0)
		find_client_team(client)->num_members--;
	if (g_env.clients == client)
		g_env.clients = client->next;
	else
	{
		previous = g_env.clients;
		while (previous->next && previous->next != client)
			previous = previous->next;
		if (previous->next == client)
			previous->next = client->next;
		delete_all_commands(client);
		free(client);
	}
	if (num_clients() < g_env.settings.num_start_clients)
		g_env.settings.num_unused_conn++;
}

void		delete_gfx_client(t_client *client)
{
	t_client	*previous;

	if (!client)
		return ;
	if (g_env.gfx_cli == client)
		g_env.gfx_cli = client->next;
	else
	{
		previous = g_env.gfx_cli;
		while (previous->next && previous->next != client)
			previous = previous->next;
		if (previous->next == client)
			previous->next = client->next;
		delete_all_commands(client);
		free(client);
	}
}

void		delete_all_clients(void)
{
	t_client	*client;
	t_client	*tmp;

	client = g_env.clients;
	while (client)
	{
		tmp = client;
		client = client->next;
		delete_client(tmp);
	}
	client = g_env.gfx_cli;
	while (client)
	{
		tmp = client;
		client = client->next;
		delete_client(tmp);
	}
}

t_client	*find_client_by_id(int id)
{
	t_client	*client;

	client = g_env.clients;
	while (client && client->id != id)
		client = client->next;
	return (client);
}
