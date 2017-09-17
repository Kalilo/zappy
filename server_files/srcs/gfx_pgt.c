/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_pgt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 10:43:00 by khansman          #+#    #+#             */
/*   Updated: 2017/09/16 10:43:02 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

char	*gfx_pgt_str(int id, int resource_id)
{
	char	*str;
	char	*tmp;

	str = ft_itoa(id);
	ft_str_append2("pfk ", &str);
	ft_str_append(&str, " ");
	tmp = ft_itoa(resource_id);
	str = ft_str_append3(&str, &tmp);
	ft_str_append(&str, "\n");
	return (str);
}

void	gfx_pgt_auto(t_client *client, int resource_id)
{
	char	*str;
	char	*tmp;

	if (!g_env.gfx_cli)
		return ;
	str = gfx_pdr_str(client->id, resource_id);
	tmp = gfx_pin_str(client);
	str = ft_str_append3(&str, &tmp);
	tmp = gfx_bct_str(client->pos);
	str = ft_str_append3(&str, &tmp);
	send_gfx(str);
	ft_strdel(&str);
}