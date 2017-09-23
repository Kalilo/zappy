#ifndef server_hpp
# define server_hpp
# include <iostream>

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <string.h>
# include <arpa/inet.h>

# include "main.h"


class server
{
	private:
		char	*line;//gets line from server-side.
		int		sockfd;

	public:
		server(void);
		server(int ac, char **av);
		~server(void);
		char	*&getline(void);
		int		&getsockfd(void);
		void	connect_(int ac, char **av);
		int		choose_pc_port(void);// /Connect  (as required by the pdf)	
		int		connect_client(char *ip_address, int port);//perfect for lib function
};
#endif
