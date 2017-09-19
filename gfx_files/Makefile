SRCS =	main.cpp get_next_line.cpp

OBJS = ${SRCS:.c=.o}

NAME = gfx

CFLAGS = -I. -g3 -Wall -Werror -Wextra
LDFLAGS = 

CC = g++

all:
		g++ -o ${NAME} ${OBJS} ${LDFLAGS}

clean:
		make fclean

fclean:
		rm -rf gfx

re:		fclean all
