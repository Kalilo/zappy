/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_pdi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 11:02:42 by khansman          #+#    #+#             */
/*   Updated: 2017/09/16 11:02:43 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

char	*gfx_pdi_str(int id)
{
	char	*str;

	str = ft_itoa(id);
	ft_str_append2("pdi ", &str);
	ft_str_append(&str, "\n");
	return (str);
}

void	gfx_pdi_auto(t_client *client)
{
	char	*str;

	if (!g_env.gfx_cli)
		return ;
	str = gfx_pdi_str(client->id);
	send_gfx(str);
	ft_strdel(&str);
}
