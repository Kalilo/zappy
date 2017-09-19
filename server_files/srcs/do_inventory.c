/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_inventory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 14:10:11 by khansman          #+#    #+#             */
/*   Updated: 2017/09/09 14:10:12 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

/*
** Might want to recode a more efficient method of gathering the inventory
*/

char	*take_inventory(t_inventory *inventory)
{
	char	*str;
	char	*tmp;

	str = ft_itoa(inventory->linemate);
	ft_str_append2("{linemate ", &str);
	ft_str_append(&str, ", deraumere ");
	tmp = ft_itoa(inventory->deraumere);
	str = ft_str_append3(&str, &tmp);
	ft_str_append(&str, ", sibur ");
	tmp = ft_itoa(inventory->sibur);
	str = ft_str_append3(&str, &tmp);
	ft_str_append(&str, ", mendiane ");
	tmp = ft_itoa(inventory->mendiane);
	str = ft_str_append3(&str, &tmp);
	ft_str_append(&str, ", phiras ");
	tmp = ft_itoa(inventory->phiras);
	str = ft_str_append3(&str, &tmp);
	ft_str_append(&str, ", thystame ");
	tmp = ft_itoa(inventory->thystame);
	str = ft_str_append3(&str, &tmp);
	ft_str_append(&str, ", food ");
	tmp = ft_itoa(inventory->food);
	str = ft_str_append3(&str, &tmp);
	ft_str_append(&str, "}\n");
	return (str);
}

void	do_inventory(t_client *client)
{
	char	*str;

	str = take_inventory(&client->inventory);
	write_msg_to_sock(client->sock, str);
	ft_strdel(&str);
	client->delay -= 1;
}
