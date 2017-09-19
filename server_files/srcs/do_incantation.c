/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_incantation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 15:52:14 by khansman          #+#    #+#             */
/*   Updated: 2017/09/12 15:52:15 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

char	enough_clients_to_incantate(t_client *client)
{
	t_cli	*cli;
	int		level;

	level = 0;
	cli = MAP(client->pos.x, client->pos.y).players;
	while (cli)
	{
		if (cli->client)
			level += cli->client->level;
		cli = cli->next;
	}
	if (client->level == 1)
		return (1);
	else if (client->level == 2)
		return (level >= 4);
	else if (client->level == 3)
		return (level >= 6);
	else if (client->level == 4)
		return (level >= 12);
	else if (client->level == 5)
		return (level >= 20);
	else if (client->level == 6)
		return (level >= 36);
	return (level >= 42);
}

/*
** Formatted to easily translate values from table in pdf
*/
char	can_incanate(t_client *client, t_inventory *inventory, int level)
{
	if (!enough_clients_to_incantate(client))
		return (0);
	if (level == 1)
		return (I_CHECK_1(1, 0));
	if (level == 2)
		return (I_CHECK_1(1, 1) && I_CHECK_2(1, 0));
	if (level == 3)
		return (I_CHECK_1(2, 0) && I_CHECK_2(1, 0) && I_CHECK_3(2, 0));
	if (level == 4)
		return (I_CHECK_1(1, 1) && I_CHECK_2(2, 0) && I_CHECK_3(1, 0));
	if (level == 5)
		return (I_CHECK_1(1, 2) && I_CHECK_2(1, 3));
	if (level == 6)
		return (I_CHECK_1(1, 2) && I_CHECK_2(3, 0) && I_CHECK_3(1, 0));
	if (level == 7)
		return (I_CHECK_1(2, 2) && I_CHECK_2(2, 2) && I_CHECK_3(2, 1));
	return (0);
}

void	incanate_invent_adjust(t_inventory *inventory, int level)
{
	if (level == 1)
		I_ADJ(-1, 0, 0, 0, 0, 0);
	else if (level == 2)
		I_ADJ(-1, -1, -1, 0, 0, 0);
	else if (level == 3)
		I_ADJ(-2, 0, -1, 0, -2, 0);
	else if (level == 4)
		I_ADJ(-1, -1, -2, 0, -1, 0);
	else if (level == 5)
		I_ADJ(-1, -2, -1, -3, 0, 0);
	else if (level == 6)
		I_ADJ(-1, -2, -3, 0, -1, 0);
	else if (level == 7)
		I_ADJ(-2, -2, -2, -2, -2, -1);
}

void	pre_incanation(t_client *client)
{
	if (!can_incanate(client, &client->inventory, client->level))
	{
		write_msg_to_sock(client->sock, "ko\n");
		delete_command(client, client->command);
		return ;
	}
	gfx_pic_auto(client->pos, client->level);
}

void	do_incantation(t_client *client)
{
	char	*str;

	if (!can_incanate(client, &client->inventory, client->level))
	{
		write_msg_to_sock(client->sock, "ko\n");
		return ;
	}
	incanate_invent_adjust(&client->inventory, client->level++);
	str = ft_itoa(client->level);
	ft_str_append2("elevation in progress current level : ", &str);
	ft_str_append(&str, "\n");
	write_msg_to_sock(client->sock, str);
	ft_strdel(&str);
	gfx_pic_auto(client->pos, client->level);
	client->delay -= 300;
	if (has_team_won(client->team_id))
		end_game(find_client_team(client));
}
