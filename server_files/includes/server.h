/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khansman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 10:10:12 by khansman          #+#    #+#             */
/*   Updated: 2017/09/05 10:10:14 by khansman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

/*
** ----------\
** Includes   |
** ----------/
*/

# include "../../includes/shared.h"

/*
** ----------\
** Defines    |
** ----------/
*/

/*
** limits
*/
# define MAX_CLIENTS	SHRT_MAX

/*
** shorthand
*/
# define MASTER_SOCK	g_env.main_sock.sock
# define MASTER_OPT		g_env.main_sock.sock_opt
# define MASTER_ADDR	g_env.main_sock.addr
# define MASTER_ADDRLEN	g_env.main_sock.addrlen
# define MASTER_MAX_SD	g_env.main_sock.max_sd

# define INPUT_FLAG(X)	g_env.settings.set_flags.X
# define SET_FLAG(X)	(!INPUT_FLAG(X) && (INPUT_FLAG(X) = 1))

/*
** enums
*/
typedef enum		e_direction
{
	north,
	east,
	south,
	west
}					t_direction;

/*
** ----------\
** Structures |
** ----------/
*/

/*
** General
*/
typedef struct		s_flags
{
	char			p:1;
	char			x:1;
	char			y:1;
	char			n:1;
	char			c:1;
	char			t:1;
}					t_flags;

typedef struct		s_client
{
	unsigned int	sock;
	int				team_id;
	unsigned int	pos_x;
	unsigned int	pos_y;
	t_direction		direction;
	int				delay;
	//inventory
	//buffer of commands
	//next client
}					t_struct;

typedef struct		s_team
{
	char			*name;
	int				id;
	unsigned int	num_members;
	unsigned int	max_members;
	struct s_team	*next;
}					t_team;

/*
** env components
*/
typedef struct		s_main_sock
{
	int				sock_opt;
	int				sock;
	int				addrlen;
	int				max_sd;
	t_sock_addrin	addr;
}					t_main_sock;

typedef struct		s_settings
{
	unsigned int	port;
	unsigned int	width;
	unsigned int	height;
	unsigned int	num_teams;
	unsigned int	num_start_clients;
	float			fps;
	t_team			*teams;
	t_flags			set_flags;
}					t_settings;

/*
** env
*/
typedef struct		s_env
{
	t_main_sock		main_sock;
	int				active_sock;
	t_settings		settings;
}					t_env;

/*
** ----------\
** Globals    |
** ----------/
*/

# ifdef SERVER_MAIN

t_env				g_env;

# else

extern t_env		g_env;

# endif

/*
** ----------\
** Prototypes |
** ----------/
*/

/*
** accept_new_client.c
*/
void				accept_new_client(void);

/*
** init.c
*/
void				sig_listener(int signo);
void				sig_setter(void);
char				init_main_socket(int port);
void				set_defults(void);

/*
** input_flags.c
*/
char				is_input_flag_set(char *flag);

/*
** parse_arguments.c
*/
void				parse_arguments(int ac, char **av);

/*
**                                /----------\                                **
** ----- ----- ----- ----- ----- |  The End   | ----- ----- ----- ----- ----- **
**                                \----------/                                **
*/
#endif
