/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_ebo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 14:27:32 by khansman          #+#    #+#             */
/*   Updated: 2017/09/16 14:27:37 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

char	*gfx_ebo_str(int id)
{
	char	*str;

	str = ft_itoa(id);
	ft_str_append2("ebo ", &str);
	ft_str_append(&str, "\n");
	return (str);
}

void	gfx_ebo_auto(t_egg *egg)
{
	char	*str;

	if (!g_env.gfx_cli)
		return ;
	str = gfx_ebo_str(egg->id);
	send_gfx(str);
	ft_strdel(&str);
}
