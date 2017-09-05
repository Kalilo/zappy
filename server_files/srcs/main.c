/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 10:26:56 by khansman          #+#    #+#             */
/*   Updated: 2017/09/05 10:26:58 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define SERVER_MAIN
#include "../includes/server.h"

int		main(int ac, char **av)
{
	ft_bzero(&g_env, sizeof(t_env));
	parse_arguments(ac, av);
	set_defults();
	return (0);
}
