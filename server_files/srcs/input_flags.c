/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 16:38:50 by khansman          #+#    #+#             */
/*   Updated: 2017/09/05 16:38:55 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

char	is_input_flag_set(char *flag)
{
	if (!ft_strcmp(flag, "-p"))
		return (INPUT_FLAG(p));
	if (!ft_strcmp(flag, "-x"))
		return (INPUT_FLAG(x));
	if (!ft_strcmp(flag, "-y"))
		return (INPUT_FLAG(y));
	if (!ft_strcmp(flag, "-n"))
		return (INPUT_FLAG(n));
	if (!ft_strcmp(flag, "-c"))
		return (INPUT_FLAG(c));
	if (!ft_strcmp(flag, "-t"))
		return (INPUT_FLAG(t));
	if (!ft_strcmp(flag, "-h") || !ft_strcmp(flag, "--help"))
		return (0);
	error_quit(ft_strjoin("unrecognized input flag: ", flag));
	return (0);
}
