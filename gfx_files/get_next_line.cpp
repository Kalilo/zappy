/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smahomed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 15:43:05 by smahomed          #+#    #+#             */
/*   Updated: 2016/12/13 18:25:07 by smahomed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*h(char *s, char *t)
{
	char	*tmp;
	int		h;

	h =  strlen(s) + strlen(t);
	tmp = (char *)malloc(sizeof(char) * (h + 1));
	 strcpy(tmp, s);
	 strcat(tmp, t);
	return (tmp);
}

int		get_next_line(const int fd, char **line)
{
	char			*u;
	char			*t;
	int				c[2];
	static char		*s[42 + 1];
	char			b[BUFF_SIZE];

	if (!line || fd < 0 || BUFF_SIZE < 0)
		return (-1);
	c[1] = 0;
	while ((c[0] = read(fd, b, BUFF_SIZE)) > 0)
	{
		c[1] = 1;
		INPUT;
		OUTPUT;
	}
	if (c[0] < 0)
		return (-1);
	OUTPUT;
	if (s[fd] && (c[1] || s[fd][0]) && !(strstr(s[fd], "\n")))
		SPECIAL;
	return (0);
}
