#include "main.h"
#define BUF_SIZE 512

main	_main;

int		receive_line(int state, int sockfd, char *recvline)
{
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

int		connect_client(char *ip_address, int port)//perfect for lib function
{
	int			sockfd;
	struct sockaddr_in	servaddr;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		write(2, "Problem in creating the socket\n", 31);
		exit(2);
	}
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(ip_address);
	servaddr.sin_port =  htons(port);
	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		write(2, "Problem in connecting to the server\n", 36);
		exit(3);
	}
	return (sockfd);
}

int		choose_pc_port(void)// /Connect  (as required by the pdf)
{
	int		b;
	char		*t;
	int		buf_len;
	char		buf[512 + 1];

	b = 0;
	write(1, "\e[37mwarning:\e[0m /Connect <machine> <port>$> ", 46);
	while (!b && (buf_len = read(0, buf, 512)) > 0)
	{
		buf[buf_len] = '\0';
		if (buf_len < 256 && (t = strstr(buf, " ")))
		{
			t[0] = '\0';
			return (connect_client(buf, atoi(&t[1])));
			b = 1;
		}
		else
			write(1, "\e[37mwarning:\e[0m /Connect <machine> <port>$> ", 46);
	}
	return (0);
}




int	main(int ac, char **av)
{
	t_env	e;
	pid_t	f;

	e.state = 1;//alive
	if (ac < 3)
		e.sockfd = choose_pc_port();
	else
		e.sockfd = connect_client(av[1], atoi(av[2]));
//	args management here.
//	if (!(f = fork()))//will either read from here.(if server based timer)
//		e.state = receive_line(e.state, e.sockfd, malloc(sizeof(char) * 4096));
	while (1)//gameloop
	{
		//or will read from server from here (if this client is doing the timing)
		//render(which will be added to repo later)
	}
	exit(0);
	return (0);
}
