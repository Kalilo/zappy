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

# include <math.h>

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

# define READ_FDS		g_env.main_sock.read_fds
# define ACTIVE_SOCK	g_env.active_sock
# define GNL_LINE		g_env.line

# define G_WIDTH		g_env.settings.width
# define G_HEIGHT		g_env.settings.height
# define MAP(X,Y)		g_env.map[X][Y]

/*
** shortened code
*/
# define INPUT_FLAG(X)	g_env.settings.set_flags.X
# define SET_FLAG(X)	(!INPUT_FLAG(X) && (INPUT_FLAG(X) = 1))

# define TAKE(X)		inventory->X--,client->inventory.X++
# define PUT(X)			inventory->X++,client->inventory.X--

# define REP_APPEND(X)	while(k--)ft_str_append(&str,X)

# define MOVE_NW		pos.x--, pos.y++
# define MOVE_NE		pos.x++, pos.y++
# define MOVE_SE		pos.x++, pos.y--
# define MOVE_SW		pos.x--, pos.y--

# define I_CHECK_1(X,Y)	inventory->linemate>=X&&inventory->deraumere>=Y
# define I_CHECK_2(X,Y)	inventory->sibur>=X&&inventory->mendiane>=Y
# define I_CHECK_3(X,Y)	inventory->phiras>=X&&inventory->thystame>=Y

# define I_ADJ_1(X,Y)	inventory->linemate+=X,inventory->deraumere+=Y
# define I_ADJ_2(X,Y)	inventory->sibur+=X,inventory->mendiane+=Y
# define I_ADJ_3(X,Y)	inventory->phiras+=X,inventory->thystame+=Y
# define I_ADJ(X,Y,Z,U,V,W) I_ADJ_1(X,Y),I_ADJ_2(Z,U),I_ADJ_3(V,W)

# define CLOSEST_CLI	shortest_dist = tmp, closest
# define IS_CLOSER(X)	((tmp = ft_dist(src, X)) < shortest_dist)

# define CLI_POS		(t_coord){client->pos.x, client->pos.y}

/*
** enums
*/
typedef enum		e_direction
{
	no_direction = -1,
	north,
	north_east,
	east,
	south_east,
	south,
	south_west,
	west,
	north_west
}					t_direction;

/*
** ----------\
** Structures |
** ----------/
*/

/*
** Coordination
*/
typedef struct		s_coord
{
	int				x;
	int				y;
}					t_coord;

/*
** Gameplay
*/
typedef struct		s_inventory
{
	unsigned short	linemate;
	unsigned short	deraumere;
	unsigned short	sibur;
	unsigned short	mendiane;
	unsigned short	phiras;
	unsigned short	thystame;
	unsigned short	food;
}					t_inventory;

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

typedef struct		s_comm
{
	char			*str;
	struct s_comm	*next;
}					t_comm;

typedef struct		s_client
{
	unsigned int	sock;
	int				team_id;
	// unsigned int	pos_x;
	// unsigned int	pos_y;
	t_coord			pos;
	t_direction		direction;
	int				delay;
	t_inventory		inventory;
	int				num_commands;
	t_comm			*command;
	int				level;
	struct s_client	*next;
}					t_client;

typedef struct		s_cli
{
	t_client		*client;
	struct s_cli	*next;
}					t_cli;

typedef struct		s_egg
{
	int				team_id;
	t_coord			pos;
	struct s_egg	*next;
}					t_egg;

typedef struct		s_tile
{
	t_inventory		inventory;
	t_cli			*players;
	t_egg			*eggs;
}					t_tile;

typedef struct		s_team
{
	char			*name;
	int				id;
	unsigned int	num_members;
	// unsigned int	max_members;
	int				avaliable_cons;
	t_egg			*eggs;
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
	fd_set			read_fds;
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
	char			*line;
	t_settings		settings;
	t_client		*clients;
	t_tile			**map;
	char			play;
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
** cli_lst.c
*/
t_cli				*new_cli(t_tile *tile);
void				delete_cli(t_tile *tile, t_client *client);
void				move_cli(t_client *client, t_direction direction);

/*
** client_lst.c
*/
t_client			*new_client(unsigned int sock);
void				delete_client(t_client *client);
void				delete_all_clients(void);

/*
** command_lst.c
*/
t_comm				*new_command(t_client *client, char *comm_str);
void				delete_command(t_client *client, t_comm *command);
void				delete_all_commands(t_client *client);

/*
** command_validation.c
*/
char				valid_command(char *str);
char				can_do_command(char *str, int delay);

/*
** coords.c
*/
t_coord				move_coord(t_coord pos, t_direction direction);

/*
** direction.c
*/
t_direction			opposite_direction(t_direction direction);
t_direction			tangent_right_direction(t_direction direction);
t_direction			tangent_left_direction(t_direction direction);
t_direction			adjacent_right_direction(t_direction direction);
t_direction			adjacent_left_direction(t_direction direction);

/*
** direction2.c
*/
t_direction			inc_dir(t_direction dir, int amount);
t_direction			dec_dir(t_direction dir, int amount);
int					north_diff(t_direction dir);

/*
** do_advance.c
*/
void				do_advance(t_client *client);

/*
** do_broadcast.c
*/
t_direction			incomming_direction(t_coord src, t_coord dest);
t_coord				closest_coord(t_coord src, t_coord dest);
void				send_msg(t_client *client, char *msg);
void				do_bradcast(t_client *client, char *msg);

/*
** do_connect_nbr.c
*/
void				do_connect_nbr(t_client *client);

/*
** do_fork.c
*/
void				do_fork(t_client *client);

/*
** do_incantation.c
*/
char				enough_clients_to_incantate(int level);
char				can_incanate(t_inventory *inventory, int level);
void				incanate_invent_adjust(t_inventory *inventory, int level);
void				do_incantation(t_client *client);

/*
** do_inventory.c
*/
char				*take_inventory(t_inventory *inventory);
void				do_inventory(t_client *client);

/*
** do_kick.c
*/
void				send_moving_msg(int sock, t_direction direction);
void				do_kick(t_client *client);

/*
** do_left.c
*/
void				do_left(t_client *client);

/*
** do_put.c
*/
void				do_put(t_client *client, char *what);

/*
** do_right.c
*/
void				do_right(t_client *client);

/*
** do_see.c
*/
char				*sum_tile_content(t_tile *tile, t_client *client);
char				*sum_range(t_coord min, t_coord max, t_direction dir,
					t_client *client);
char				*get_in_sight(t_client *client);
void				do_see(t_client *client);

/*
** do_take.c
*/
void				do_take(t_client *client, char *what);

/*
** egg_lst.c
*/
void				lay_egg(t_client *client);
t_coord				hatch_egg(t_team *team);

/*
** gameplay.c
*/
void				play_choice(void);
void				inc_user_delays(void);
char				run_iteration(void);

/*
** init.c
*/
void				sig_listener(int signo);
void				sig_setter(void);
char				init_main_socket(int port);
void				set_defults(void);
void				init_gameplay(void);

/*
** input_flags.c
*/
char				is_input_flag_set(char *flag);

/*
** manage_clients.c
*/
void				manage_clients(void);

/*
** maths.c
*/
float				ft_dist(t_coord a, t_coord b);

/*
** parse_arguments.c
*/
void				parse_arguments(int ac, char **av);

/*
** populate_map.c
*/
void				add_random_gem(int x, int y);
void				populate_map(void);

/*
** prep_client_sockets.c
*/
void				prep_client_sockets(void);

/*
** run_command.c
*/
void				run_command(t_client *client, char *command);

/*
** team_lst.c
*/
t_team				*find_client_team(t_client *client);

/*
**                                /----------\                                **
** ----- ----- ----- ----- ----- |  The End   | ----- ----- ----- ----- ----- **
**                                \----------/                                **
*/
#endif
