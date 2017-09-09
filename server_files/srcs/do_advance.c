/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_advance.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 14:09:22 by khansman          #+#    #+#             */
/*   Updated: 2017/09/09 14:09:26 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

void	do_advance(t_client *client)
{
	move_cli(client, client->direction);
		write_msg_to_sock(client->sock, "ok\n");
}
