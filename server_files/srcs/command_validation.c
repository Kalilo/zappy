/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 13:38:19 by khansman          #+#    #+#             */
/*   Updated: 2017/09/09 13:38:20 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

char	valid_command(char *str)
{
	if (!ft_strcmp(str, "advance"))
		return (1);
	if (!ft_strcmp(str, "right"))
		return (1);
	if (!ft_strcmp(str, "left"))
		return (1);
	if (!ft_strcmp(str, "see"))
		return (1);
	if (!ft_strcmp(str, "inventory"))
		return (1);
	if (!ft_strncmp(str, "take ", 5))
		return (1);
	if (!ft_strncmp(str, "put ", 4))
		return (1);
	if (!ft_strcmp(str, "kick"))
		return (1);
	if (!ft_strncmp(str, "broadcast ", 10))
		return (1);
	if (!ft_strcmp(str, "incantation"))
		return (1);
	if (!ft_strcmp(str, "fork"))
		return (1);
	if (!ft_strcmp(str, "connect_nbr"))
		return (1);
	return (0);
}

char	can_do_command2(char *str, int delay)
{
	if (!ft_strncmp(str, "b", 1))
		return (delay >= 7);
	if (!ft_strncmp(str, "inc", 3))
		return (delay >= 300);
	if (!ft_strncmp(str, "f", 1))
		return (delay >= 42);
	if (!ft_strncmp(str, "c", 1))
		return (1);
	if (!(ft_strncmp(str, "e", 1)))
		return (delay >= 600);
	return (0);
}

char	can_do_command(char *str, int delay)
{
	if (!ft_strncmp(str, "a", 1))
		return (delay >= 7);
	if (!ft_strncmp(str, "r", 1))
		return (delay >= 7);
	if (!ft_strncmp(str, "l", 1))
		return (delay >= 7);
	if (!ft_strncmp(str, "s", 1))
		return (delay >= 7);
	if (!ft_strncmp(str, "inv", 3))
		return (delay >= 1);
	if (!ft_strncmp(str, "t", 1))
		return (delay >= 7);
	if (!ft_strncmp(str, "p", 1))
		return (delay >= 7);
	if (!ft_strncmp(str, "k", 1))
		return (delay >= 7);
	return (can_do_command2(str, delay));
}
