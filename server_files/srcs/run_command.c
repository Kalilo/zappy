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

void	run_command(t_client *client, char *command)
{
	if (!ft_strncmp(command, "a", 1))
		do_advance(client);
	else if (!ft_strncmp(command, "r", 1))
		do_right(client);
	else if (!ft_strncmp(command, "l", 1))
		do_left(client);
	else if (!ft_strncmp(command, "s", 1))
		(void)command;
	else if (!ft_strncmp(command, "inv", 3))
		(void)command;
	else if (!ft_strncmp(command, "t", 1))
		(void)command;
	else if (!ft_strncmp(command, "p", 1))
		(void)command;
	else if (!ft_strncmp(command, "k", 1))
		do_kick(client);
	else if (!ft_strncmp(command, "b", 1))
		(void)command;
	else if (!ft_strncmp(command, "inc", 3))
		(void)command;
	else if (!ft_strncmp(command, "f", 1))
		(void)command;
	else if (!ft_strncmp(command, "c", 1))
		(void)command;
	delete_command(client, client->command);
}
