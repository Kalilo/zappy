/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_lst2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 07:08:28 by khansman          #+#    #+#             */
/*   Updated: 2017/09/20 07:08:29 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

unsigned int	num_clients(void)
{
	t_client	*client;
	int			k;

	k = 0;
	client = g_env.clients;
	while (client)
	{
		k++;
		client = client->next;
	}
	return (k);
}

unsigned int	num_clients_in_team(int team_id)
{
	t_client	*client;
	int			k;

	k = 0;
	client = g_env.clients;
	while (client)
	{
		if (client->team_id == team_id)
			k++;
		client = client->next;
	}
	return (k);
}
