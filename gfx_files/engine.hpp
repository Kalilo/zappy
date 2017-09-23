#ifndef engine_hpp
# define engine_hpp
# include <iostream>
# include "server.hpp"

class engine
{
	private:
		server	connector;
		//map   3d: stones food + ( player coords?)
		
	public:
		engine(void);
		~engine(void);
		server	&getconnector(void);

};
#endif
