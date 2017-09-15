/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_sgt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 16:33:32 by khansman          #+#    #+#             */
/*   Updated: 2017/09/15 16:33:34 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

void	gfx_sgt(t_client *client)
{
	char	*str;

	str = ft_itoa(g_env.settings.fps);
	ft_str_append2("sgt ", &str);
	ft_str_append(&str, "\n");
	write_msg_to_sock(client->sock, str);
	ft_strdel(&str);
}
