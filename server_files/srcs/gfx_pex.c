/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_pex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 08:59:05 by khansman          #+#    #+#             */
/*   Updated: 2017/09/16 08:59:06 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

char	*gfx_pex_str(t_client *client)
{
	char	*str;

	str = ft_itoa(client->id);
	ft_str_append2("pex ", &str);
	ft_str_append(&str, "\n");
	return (str);
}

void	gfx_pex_auto(t_client *client)
{
	char	*str;

	if (!g_env.gfx_cli)
		return ;
	str = gfx_pex_str(client);
	send_gfx(str);
	ft_strdel(&str);
}