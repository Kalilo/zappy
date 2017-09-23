#ifndef engine_hpp
# define engine_hpp
# include <iostream>
# include <vector>


# include "server.hpp"
# include "map.hpp"

class engine
{
	private:
		server	connector;
//		std::vector< std::vector< std::vector<int> > >	map_;//map   3d: stones food + ( player coords?)
		map												mapper;

	public:
		engine(void);
		~engine(void);
		server	&getconnector(void);
		map		&getmapper(void);
};
#endif
