#include "server.hpp"

server::server(void)
{
}

server::~server(void)
{
}


void	server::connect_(int ac, char **av)
{//will connect using this function.
//set socket:
	if (ac < 3)
		this->sockfd = this->choose_pc_port();
	else
		this->sockfd = this->connect_client(av[1], atoi(av[2]));
//writing the welcome message from server-side:
	get_next_line(this->sockfd, &(this->line));
	write(1, this->line, strlen(this->line));
	write(1, "\n", 1);
//registering this client as a gfx with server-side:
	write(this->sockfd, "GRAPHIC\n", 8);
}

int		server::choose_pc_port(void)
{//if no pc port was parsed as an arg then get input from user...
	int			b;
	char		*t;
	int			buf_len;
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

int		server::connect_client(char *ip_address, int port)
{	//perfect for a lib function
	int					sockfd;
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



char	*&server::getline(void)
{
	return (this->line);
}


int		&server::getsockfd(void)
{
	return (this->sockfd);
}

