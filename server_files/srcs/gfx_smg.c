/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_smg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 14:33:30 by khansman          #+#    #+#             */
/*   Updated: 2017/09/16 14:33:34 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

char	*gfx_smg_str(char *msg)
{
	char	*str;

	str = ft_strjoin("smg ", msg);
	ft_str_append(&str, "\n");
	return (str);
}

void	gfx_smg_auto(char *msg)
{
	char	*str;

	if (!g_env.gfx_cli)
		return ;
	str = gfx_smg_str(msg);
	send_gfx(str);
	ft_strdel(&str);
}
