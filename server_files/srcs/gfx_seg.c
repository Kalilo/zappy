/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_seg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/17 10:35:12 by khansman          #+#    #+#             */
/*   Updated: 2017/09/17 10:35:13 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

char	*gfx_seg_str(char *team)
{
	char	*str;

	str = ft_strjoin("seg ", team);
	ft_str_append(&str, "\n");
	return (str);
}

void	gfx_seg_auto(char *team)
{
	char	*str;

	if (!g_env.gfx_cli)
		return ;
	str = gfx_seg_str(team);
	send_gfx(str);
	ft_strdel(&str);
}
