/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_see.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 14:09:54 by khansman          #+#    #+#             */
/*   Updated: 2017/09/09 14:09:55 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

char	*sum_time_content(t_tile *tile)
{
	char	*str;
	int		k;
	t_cli	*cli;

	str = ft_strdup("");
	k = tile->inventory.linemate;
	REP_APPEND(" linemate");
	k = tile->inventory.deraumere;
	REP_APPEND(" deraumere");
	k = tile->inventory.sibur;
	REP_APPEND(" sibur");
	k = tile->inventory.mendiane;
	REP_APPEND(" mendiane");
	k = tile->inventory.phiras;
	REP_APPEND(" phiras");
	k = tile->inventory.thystame;
	REP_APPEND(" thystame");
	k = tile->inventory.food;
	REP_APPEND(" food");
	cli = tile->players;
	while (cli && ((cli = cli->next) || 1))
		ft_str_append(&str, " player");
	return (str);
}
