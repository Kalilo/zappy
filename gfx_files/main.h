#ifndef MAIN_H
# define MAIN_H
# include <stdlib.h>
# include <stdio.h>

# include <unistd.h>
# include <sys/wait.h>

# include "get_next_line.h"

# include "server.hpp"

typedef struct  s_env
{
	int		sockfd;
	int		state;//probably not needed.
}			t_env;

//	engine class
//should create the environmental var
class	main
{
	private:
	public:
};

//place in server.hpp
#endif
