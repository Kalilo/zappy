/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_msz.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 14:04:07 by khansman          #+#    #+#             */
/*   Updated: 2017/09/15 14:04:08 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

void	gfx_msz(t_client *client)
{
	char	*str;

	str = coord_to_str((t_coord){G_WIDTH, G_HEIGHT});
	ft_str_append2("msz ", &str);
	ft_str_append(&str, "\n");
	write_msg_to_sock(client->sock, str);
	ft_strdel(&str);
}
