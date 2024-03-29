# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggroener <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/28 11:16:22 by ggroener          #+#    #+#              #
#    Updated: 2016/12/09 16:35:20 by khansman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = server

SRCS_NAME_1 =	accept_new_client.c			\
				cli_lst.c					\
				client_lst.c				\
				client_lst2.c				\
				command_lst.c				\
				command_validation.c		\
				coords.c					\
				death_event.c				\
				direction.c					\
				direction2.c				\
				do_advance.c				\
				do_broadcast.c				\
				do_connect_nbr.c			\
				do_egg.c					\
				do_fork.c					\
				do_incantation.c			\
				do_inventory.c				\
				do_kick.c					\

SRCS_NAME_2 =	do_left.c					\
				do_put.c					\
				do_right.c					\
				do_see.c					\
				do_take.c					\
				egg_lst.c					\
				game_end.c					\
				gameplay.c					\
				gfx_bct.c					\
				gfx_cli.c					\
				gfx_ebo.c					\
				gfx_edi.c					\
				gfx_eht.c					\
				gfx_enw.c 					\

SRCS_NAME_3 =	gfx_mct.c					\
				gfx_msz.c					\
				gfx_pbc.c					\
				gfx_pdi.c					\
				gfx_pdr.c					\
				gfx_pex.c					\
				gfx_pfk.c					\
				gfx_pgt.c					\
				gfx_pic.c					\
				gfx_pie.c					\
				gfx_pin.c					\
				gfx_plv.c					\
				gfx_pnw.c					\
				gfx_ppo.c					\
				gfx_seg.c					\

SRCS_NAME_4 =	gfx_sgt.c					\
				gfx_smg.c					\
				gfx_sst.c					\
				gfx_tna.c					\
				init.c						\
				input_flags.c				\
				inventory.c					\
				join_team.c					\
				main.c						\
				manage_clients.c			\
				manage_gfx_commands.c		\
				maths.c						\
				parse_arguments.c			\
				populate_map.c				\
				prep_client_sockets.c		\
				run_command.c				\
				team_lst.c					\

SRCS_NAME =		$(SRCS_NAME_1)				\
				$(SRCS_NAME_2)				\
				$(SRCS_NAME_3)				\
				$(SRCS_NAME_4)				\

HEADER_NAMES =	server.h					\

ifeq ($(shell uname -s), Darwin) # Changes rules for MAC and Linux
SYS = OSX
else
SYS = LINUX
endif

CFLAGS =	-Wall -Wextra -Werror -O3 -Wno-constant-logical-operand

ifeq ($(SYS), OSX) 

CFLAGS2 = 	-Wall -Wextra -Werror -O3
else

CFLAGS2 =	-Wall -Wextra -Werror -O3

endif

CC = gcc

INCLUDES_PATH = includes/

SRCS_PATH = srcs/

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS_PATH = objs/

OBJS_NAME = $(SRCS_NAME:.c=.o)

OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))

ifeq ($(SYS), OSX)

LIBRARY = -L ../libft/ -lft
 
INCLUDES = -I includes/ -I ../libft/includes

else

LIBRARY = -L ../libft/ -lft -lm

INCLUDES = -I includes/ -I ../libft/includes

endif

HEADER = $(addprefix $(INCLUDES_PATH), $(HEADER_NAMES))

all: qme odir $(NAME)

define colourecho
	@tput setaf 14
	@echo $1
	@tput sgr0
endef

define colourecho2
	@tput setaf 2
	@echo $1
	@tput sgr0
endef

$(NAME): $(OBJS)
	@$(call colourecho, " - Making $(NAME)")
	@clear
	@$(CC) $(CFLAGS2) -o $(NAME) $^ ../shared.a $(LIBRARY) $(INCLUDES) -I$(INCLUDES_PATH)
	@clear
	@$(call colourecho, "Make Done!")

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@$(call colourecho, " - Compiling $<")
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $< -I$(INCLUDES_PATH)
	@$(call colourecho, "Compiling Done!")

odir:
	@mkdir -p $(OBJS_PATH)

clean:
	@$(call colourecho, " - Clearing object files")
	@rm -f $(OBJS)
	@$(call colourecho, "clean done!")

fclean: clean
	@$(call colourecho, "Clearing executable files")
	@rm -f $(NAME)
	@$(call colourecho, "fclean done")

re: fclean all
	@$(call colourecho, "re Done!")

run: $(NAME)
	./$(NAME)

qre:
	@$(call colourecho, " - Clearing object files")
	@rm -f $(OBJS)
	@rm -f $(NAME)
	@$(call colourecho, "clean done!")
	@make odir
	@make $(NAME)

format: norme me

norme: norm

norm:
	@$(call colourecho2, "Norminette:")
	@norminette $(addprefix $(SRCS_PATH), $(SRCS_NAME_1))
	@norminette $(addprefix $(SRCS_PATH), $(SRCS_NAME_2))
	@norminette $(addprefix $(SRCS_PATH), $(SRCS_NAME_3))
	@norminette $(addprefix $(SRCS_PATH), $(SRCS_NAME_4))
	@norminette $(HEADER)

fnorm: fnorme

fnorme:
	@$(call colourecho2, "Norminette:")
	@find $(SRCS_PATH) -name "*.c" -maxdepth 1 -type f -exec norminette  {} \;
	@find $(INCLUDES_PATH) -name "*.h" -maxdepth 1 -type f -exec norminette  {} \;

qme:
	@if [ ! -f author ]; then \
		whoami > author; \
	fi
	
me: qme
	cat -e author

submodule:
	git submodule init libft
	git submodule update
	git submodule sync -- libft

.PHONY: clean fclean re odir
