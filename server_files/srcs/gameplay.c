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

void	play_choice(void)
{
	t_client	*client;

	client = g_env.clients;
	while (client)
	{
		if (client->command &&
				can_do_command(client->command->str, client->delay))
			run_command(client, client->command->str);
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
	return (1);//if the game is still in play
}
