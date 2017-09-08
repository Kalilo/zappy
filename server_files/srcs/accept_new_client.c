/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accept_new_client.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 18:02:47 by khansman          #+#    #+#             */
/*   Updated: 2017/07/19 18:02:48 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

void	accept_new_client(void)
{
	int		sock;

	if ((sock = accept(MASTER_SOCK, (t_sock_addr *)&MASTER_ADDR,
			(socklen_t *)&MASTER_ADDRLEN)) < 0)
		error_quit("Failed to accept new client");
	ft_putendl("New client connected.");
	if (!new_client(sock))
		error_quit("Failed to create new client");
	if (write_msg_to_sock(sock, "WELCOME\n") < 1)
		error_quit("Failed to accept client connection");
}
