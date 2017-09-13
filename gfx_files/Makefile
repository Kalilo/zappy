SRCS =	main.cpp

OBJS = ${SRCS:.c=.o}

NAME = gfx

CFLAGS = -I. -g3 -Wall -Werror -Wextra
LDFLAGS = 

CC = g++
RM = rm -f

${NAME}:	${OBJS}
		${CC} -o ${NAME} ${OBJS} ${LDFLAGS}
		@make clean # shad: added

all:		${NAME}

clean:
		${RM} ${OBJS} *~ #*#

fclean:		clean
		${RM} ${NAME}

re:		fclean all
