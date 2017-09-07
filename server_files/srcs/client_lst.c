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

	if (!(client = (t_client *)calloc(sizeof(t_client), 1)))
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

void	delete_client(t_client *client)
{
	t_client	*previous;

	if (!client)
		return ;
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
}
