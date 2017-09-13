#ifndef CLIENT_H
# define CLIENT_H
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <string.h>
# include <arpa/inet.h>

# include <unistd.h>
# include <sys/wait.h>


typedef struct  s_env
{
	int     sockfd;
	int     state;//probably not needed.
}               t_env;
#endif
