/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 14:10:25 by khansman          #+#    #+#             */
/*   Updated: 2017/09/09 14:10:28 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

void	do_fork(t_client *client)
{
	write_msg_to_sock(client->sock, "ok\n");
	client->delay -= 42;
	gfx_enw_auto(client, lay_egg(client));
}

void	pre_fork(t_client *client)
{
	gfx_pfk_auto(client->id);
}
