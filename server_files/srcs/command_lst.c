/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 11:31:36 by khansman          #+#    #+#             */
/*   Updated: 2017/09/07 11:31:37 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

t_comm	*new_command(t_client *client, char *comm_str)
{
	t_comm		*command;
	t_comm		*lst;
	char		k;

	if (!(command = (t_comm *)ft_strnew(sizeof(t_comm))))
		error_quit("Insufficient memory avaliable.");
	command->str = comm_str;
	if (!(client->command))
		client->command = command;
	else
	{
		k = -1;
		lst = client->command;
		while (lst->next && (++k < 10))
			lst = lst->next;
		if (k < 10)
			lst->next = command;
		else
		{
			free(command);
			return (NULL);
		}
	}
	(client->num_commands)++;
	return (command);
}

void	delete_command(t_client *client, t_comm *command)
{
	t_comm		*previous;

	if (!client)
		return ;
	if ((!command || client->command == command) &&
		(previous = client->command))
	{
		ft_strdel(&command->str);
		client->command = previous->next;
		free(previous);
	}
	else if (client->command)
	{
		previous = client->command;
		while (previous->next && previous->next != command)
			previous = previous->next;
		if (previous->next == command)
			previous->next = command->next;
		ft_strdel(&command->str);
		free(command);
	}
	if (client->num_commands)
		client->num_commands--;
}

void	delete_all_commands(t_client *client)
{
	t_comm		*command;
	t_comm		*tmp;

	command = client->command;
	client->command = NULL;
	while (command)
	{
		tmp = command;
		command = tmp->next;
		ft_strdel(&tmp->str);
		free(tmp);
	}
}
