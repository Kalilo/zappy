/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 08:51:36 by khansman          #+#    #+#             */
/*   Updated: 2017/09/09 08:51:38 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

void	welcome_client(t_client *client)
{
	char	*str;
	char	*tmp;

	str = ft_itoa((find_client_team(client))->avaliable_cons);
	ft_str_append(&str, "\n");
	tmp = ft_itoa(G_WIDTH);
	str = ft_str_append3(&str, &tmp);
	ft_str_append(&str, " ");
	tmp = ft_itoa(G_HEIGHT);
	str = ft_str_append3(&str, &tmp);
	ft_str_append(&str, "\n");
	write_msg_to_sock(client->sock, str);
	ft_strdel(&str);
	gfx_pnw_auto(client);
}

void	play_choice(void)
{
	t_client	*client;

	client = g_env.clients;
	while (client)
	{
		if (client->command)
		{
			if (!client->level)
			{
				if (join_team(client, client->command->str))
					welcome_client(client);
				else
					write_msg_to_sock(client->sock, "-1\n");
				delete_command(client, client->command);
			}
			else if (client->delay == 0)
				pre_run_command(client, client->command->str);
			else if (can_do_command(client->command->str, client->delay))
				run_command(client, client->command->str);
		}
		client = client->next;
	}
}

void	inc_user_delays(void)
{
	t_client	*client;
	t_client	*previous;

	previous = NULL;
	client = g_env.clients;
	while (client)
	{
		if (client->command)
			client->delay++;
		if (client->level > 0)
		{
			client->life--;
			if (client->life % 126 == 0 && client->inventory.food > 0)
			{
				client->life += 126;
				client->inventory.food--;
			}
			if (client->life <= 0 && death_event(client))
				client = (previous) ? previous : g_env.clients;
		}
		previous = client;
		client = (client) ? client->next : NULL;
	}
}

char	run_iteration(void)
{
	play_choice();
	inc_user_delays();
	dec_egg_health();
	return (g_env.play);
}
