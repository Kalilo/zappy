/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_connect_nbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 14:10:39 by khansman          #+#    #+#             */
/*   Updated: 2017/09/09 14:10:40 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

void	do_connect_nbr(t_client *client)
{
	char	*num;
	t_team	*team;

	team = find_client_team(client);
	num = ft_itoa((team) ? team->avaliable_cons : -1);
	ft_str_append(&num, "\n");
	write_msg_to_sock(client->sock, num);
	ft_strdel(&num);
}
