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

	str = ft_itoa((find_client_team(client))->avaliable_cons + 1);
	ft_str_append(&str, "\n");
	tmp = ft_itoa(client->pos.x);
	str = ft_str_append3(&str, &tmp);
	ft_str_append(&str, " ");
	tmp = ft_itoa(client->pos.y);
	str = ft_str_append3(&str, &tmp);
	ft_str_append(&str, "\n");
	write_msg_to_sock(client->sock, str);
	ft_strdel(&str);
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
			else if (can_do_command(client->command->str, client->delay))
				run_command(client, client->command->str);
		}
		client = client->next;
	}
}

void	inc_user_delays(void)
{
	t_client	*client;

	client = g_env.clients;
	while (client)
	{
		if (client->command)
			client->delay++;
		client = client->next;
	}
}

char	run_iteration(void)
{
	play_choice();
	// generate resources.
	inc_user_delays();
	// check if the game is still in play
	return (g_env.play);//if the game is still in play
}
