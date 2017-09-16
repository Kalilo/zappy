/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_pfk.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 10:23:22 by khansman          #+#    #+#             */
/*   Updated: 2017/09/16 10:23:23 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

char	*gfx_pfk_str(int id)
{
	char	*str;

	str = ft_itoa(id);
	ft_str_append2("pfk ", &str);
	ft_str_append(&str, "\n");
	return (str);
}

void	gfx_pfk_auto(int id)
{
	char	*str;

	if (!g_env.gfx_cli)
		return ;
	str = gfx_pfk_str(id);
	send_gfx(str);
	ft_strdel(&str);
}
