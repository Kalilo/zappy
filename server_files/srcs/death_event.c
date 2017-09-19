/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 08:01:58 by khansman          #+#    #+#             */
/*   Updated: 2017/09/19 08:02:03 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

void	death_event(t_client *client)
{
	ft_putendl("client died...");
	write_msg_to_sock(client->sock, "death\n");
	gfx_pdi_auto(client);
	close(client->sock);
	delete_client(client);
}
