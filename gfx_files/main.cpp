#include "main.h"
#define BUF_SIZE 512
# include "engine.hpp"


//main	_main;//what is this?

engine	&e(void)
{
	static engine env;

	return (env);
}

void	*receive_line(void *ptr)//put in engine.
{
//	char	*t;//for strstr magicianary.
//	char	*line;//MOVE to engine class... to get data faster.

	while (get_next_line(e().getconnector().getsockfd(), &e().getconnector().getline()))
	{
		e().getmapper().msz();//checks to get mapsize()
		e().getmapper().bct();//places block data into mapping.
	//receive line:
		printf("%s\n", e().getconnector().getline());
	//place data in correct struct place...
	//add map_generator to use blocks to store information once map-size has been established
		free(e().getconnector().getline());
		e().getconnector().getline() = NULL;
		printf("test\n");
	}
	printf("test2\n");
	return (0);
}



int	algorithm(void)//NORMAL CLIENT ideology.
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

int	main(int ac, char **av)
{
	int			iret1;
	pthread_t	thread1;

	e();//registers as graphics engine with server-side
	e().getconnector().connect_(ac, av);
//thread to server(for good reason):
	iret1 = pthread_create( &thread1, NULL, receive_line, (void*)"server::thread");
	if(iret1)
		exit(EXIT_FAILURE + 0 * fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1));
	while (1)//gameloop
	{
		if (e().getmapper().getmap().size())
			if (e().getmapper().getmap()[0].size())
				if (e().getmapper().getmap()[0][0].size())
				{
					//engine to render here.
					e().getmapper().print_map(1);
				}
//		printf("render from engine data: msz X Y %d %d\n", e().getmapper().getmap().size() ? e().getmapper().getmap()[0].size() : -1, (e().getmapper().getmap().size() && e().getmapper().getmap()[0].size()) ? e().getmapper().getmap()[0][0].size() : -1);
		//AT interval time should send specific requests to server-side to get updates...
		//or will read from server from here (if this client is doing the timing)
		//render(which will be added to repo later)
//		exit(1);
	}
	pthread_join( thread1, NULL);
	exit(0);
	return (0);
}

