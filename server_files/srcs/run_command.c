/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 13:54:24 by khansman          #+#    #+#             */
/*   Updated: 2017/09/09 13:54:25 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

void	run_gfx_command(t_client *client, char *command)
{
	if (!ft_strcmp(command, "msz"))
		gfx_msz(client);
	else if (!ft_strncmp(command, "bct ", 4))
		gfx_bct(client, command + 4);
	else if (!ft_strcmp(command, "mct"))
		gfx_mct(client);
	else if (!ft_strcmp(command, "tna"))
		gfx_tna(client);
	else
		write_msg_to_sock(client->sock, "suc\n");
	delete_command(client, client->command);
}

void	run_command(t_client *client, char *command)
{
	if (!ft_strncmp(command, "a", 1))
		do_advance(client);
	else if (!ft_strncmp(command, "r", 1))
		do_right(client);
	else if (!ft_strncmp(command, "l", 1))
		do_left(client);
	else if (!ft_strncmp(command, "s", 1))
		do_see(client);
	else if (!ft_strncmp(command, "inv", 3))
		do_inventory(client);
	else if (!ft_strncmp(command, "t", 1))
		do_take(client, command + 5);
	else if (!ft_strncmp(command, "p", 1))
		do_put(client, command + 4);
	else if (!ft_strncmp(command, "k", 1))
		do_kick(client);
	else if (!ft_strncmp(command, "b", 1))
		do_bradcast(client, command + 10);
	else if (!ft_strncmp(command, "inc", 3))
		do_incantation(client);
	else if (!ft_strncmp(command, "f", 1))
		do_fork(client);
	else if (!ft_strncmp(command, "c", 1))
		do_connect_nbr(client);
	delete_command(client, client->command);
}
