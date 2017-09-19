/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_pbc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 09:24:41 by khansman          #+#    #+#             */
/*   Updated: 2017/09/16 09:24:43 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

char	*gfx_pbc_str(t_client *client, char *msg)
{
	char	*str;

	str = ft_itoa(client->id);
	ft_str_append2("pbc ", &str);
	ft_str_append(&str, " ");
	ft_str_append(&str, msg);
	ft_str_append(&str, "\n");
	return (str);
}

void	gfx_pbc_auto(t_client *client, char *msg)
{
	char	*str;

	if (!g_env.gfx_cli)
		return ;
	str = gfx_pbc_str(client, msg);
	send_gfx(str);
	ft_strdel(&str);
}
