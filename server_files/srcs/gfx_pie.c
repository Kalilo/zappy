/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_pie.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 10:18:00 by khansman          #+#    #+#             */
/*   Updated: 2017/09/16 10:18:01 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

char	*gfx_pie_str(t_coord pos, char sucess)
{
	char	*str;

	str = coord_to_str(pos);
	ft_str_append2("pie ", &str);
	ft_str_append(&str, (sucess) ? "1" : "0");
	ft_str_append(&str, "\n");
	return (str);
}

void	gfx_pie_auto(t_coord pos, char sucess)
{
	char	*str;

	if (!g_env.gfx_cli)
		return ;
	str = gfx_pie_str(pos, sucess);
	send_gfx(str);
	ft_strdel(&str);
}
