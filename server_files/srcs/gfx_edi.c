/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_edi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 14:31:24 by khansman          #+#    #+#             */
/*   Updated: 2017/09/16 14:31:24 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

char	*gfx_edi_str(int id)
{
	char	*str;

	str = ft_itoa(id);
	ft_str_append2("ebo ", &str);
	ft_str_append(&str, "\n");
	return (str);
}

void	gfx_edi_auto(int egg_id)
{
	char	*str;

	if (!g_env.gfx_cli)
		return ;
	str = gfx_edi_str(egg_id);
	send_gfx(str);
	ft_strdel(&str);
}
