/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 16:50:37 by khansman          #+#    #+#             */
/*   Updated: 2017/09/19 16:50:41 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

void	send_victory_message(int team_id)
{
	t_client	*client;

	client = g_env.clients;
	while (client)
	{
		if (client->team_id == team_id)
			write_msg_to_sock(client->sock, "WIN!\n");
		write_msg_to_sock(client->sock, "GAMEOVER\n");
		client = client->next;
	}
}

/*
** Send all clients GameOver message, and disconnects them
** might decide to change this behaviour
*/

void	end_game(t_team *team)
{
	send_victory_message(team->id);
	gfx_seg_auto(team->name);
	ft_putstr("GAMEOVER\nWinning Team: ");
	ft_putendl(team->name);
	delete_all_clients();
	exit(0);
}
