#include "main.h"
#define BUF_SIZE 512
# include "engine.hpp"


//main	_main;//what is this?

engine	&e(void)
{
	static engine env;

	return (env);
}


int		receive_line(int state, char *recvline)//put in engine.
{
	char	*line;//MOVE to engine class... to get data faster.

	while (get_next_line(e().getconnector().getsockfd(), &line))
	{
		//receive line:
		printf("%s\n", line);
	//place data in correct struct place...
	//add map_generator to use blocks to store information once map-size has been established
		free(line);
		printf("test\n");
	}
	printf("test2\n");

	/*
	int	len;

	while ((len = read(sockfd, recvline, 4096)) > 0)
	{
		if (!len)
		{
			memset(recvline, 0, 4096);
			free(recvline);
			write(2, "The server terminated prematurely\n", 34);
			return (0);
		}
		if (!strncmp(recvline, "/Quit", len))
			return (0);
		write(1, "\b\b\b", 3);
		write(1, recvline, len);//will do something with the received string here...
		write(1, "$> ", 3);
	}
	if (state)
		write(2, "error in reading from server\n", 29);
	free(recvline);
	*/
	return (0);
}



int	algorithm(void)
{
	//SEE (function call)
	// if player is getting hungry
	//	if food is in range
	//		approach nearest food
	//	else choose rand() direction (left, right or forward)
	// else
	//	if stone is in range
	//		if is needed by team(to level up)
	//			approach nearest stone
//DOES SOUND MAKE US MORE OR LESS LIKELY TO APPROACH THAT DIRECTION
//	AND WHEN?
	return (1);
}

// int		connect_client(char *ip_address, int port)//perfect for lib function
// {
// }

int	main(int ac, char **av)
{
	t_env	env;
	pid_t	f;
	char	*line;//put in engine.
	char	buf[1024];

	e();//registers as graphics engine with server-side
	e().getconnector().connect_(ac, av);
	if (!(f = fork()))//will read from here:
		receive_line(env.state, (char *)malloc(sizeof(char) * 4096));
	while (1)//gameloop
	{
		//printf("render from engine data\n");
		//AT interval time should send specific requests to server-side to get updates...
		//or will read from server from here (if this client is doing the timing)
		//render(which will be added to repo later)
	}
	exit(0);
	return (0);
}
