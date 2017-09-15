/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_gfx_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 15:17:54 by khansman          #+#    #+#             */
/*   Updated: 2017/09/15 15:17:58 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

void	manage_gfx_commands(void)
{
	t_client	*client;

	client = g_env.gfx_cli;
	while (client)
	{
		if (client->command)
			run_gfx_command(client, client->command->str);
		client = client->next;
	}
}
