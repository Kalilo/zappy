/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b.h                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smahomed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 15:43:36 by smahomed          #+#    #+#             */
/*   Updated: 2016/12/13 18:28:14 by smahomed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 32
# define A if(s[fd]&&(u= strstr(s[fd],"\n"))&&((u[0]='\0')||1)
# define B (*line= strdup(s[fd]))&&(t=s[fd])&&(s[fd]= strdup(&u[1])))
# define OUTPUT A && B {free(t?t:0);return 1;}
# define C u=NULL;b[c[0]]='\0';if(s[fd])
# define D free(u);}else s[fd]= strdup(b)
# define INPUT C {u=s[fd];s[fd]=h(s[fd],b); D;
# define E t=s[fd];*line= strdup(s[fd]);free(t);s[fd]=NULL;
# define SPECIAL {E;return 1;}

# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int		get_next_line(const int fd, char **line);

#endif
