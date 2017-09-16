/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_pdr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 10:31:47 by khansman          #+#    #+#             */
/*   Updated: 2017/09/16 10:31:48 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

char	*gfx_pdr_str(int id, int resource_id)
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

void	gfx_pdr_auto(int id, int resource_id)
{
	char	*str;

	if (!g_env.gfx_cli)
		return ;
	str = gfx_pdr_str(id, resource_id);
	send_gfx(str);
	ft_strdel(&str);
}
