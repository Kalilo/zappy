SRCS =	main.cpp

OBJS = ${SRCS:.c=.o}

NAME = gfx

CFLAGS = -I. -g3 -Wall -Werror -Wextra
LDFLAGS = 

CC = g++

${NAME}:
		g++ -o ${NAME} ${OBJS} ${LDFLAGS}

all:		${NAME}

clean:
		make fclean

fclean:
		rm -rf gfx

re:		fclean all
