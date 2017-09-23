#ifndef map_hpp
# define map_hpp
# include <iostream>
# include <vector>

class map
{
	private:
		std::vector< std::vector< std::vector<int> > >	map_;//map   3d: stones food + ( player coords?)
//0		(potential)player data
//1		food data
//2		stone 0 data
//3		stone 1 data
//4		stone 2 data
//5		stone 3 data
//6		stone 4 data
//7		stone 5 data

	public:
		map(void);
		~map(void);
		std::vector< std::vector< std::vector<int> > >	&getmap(void);
		int												print_map(int mapid);
		std::vector< std::vector< std::vector<int> > >	&initialize_map(std::vector< std::vector< std::vector<int> > > &map, int width, int height);
		std::vector< std::vector< std::vector<int> > >  &generate_map(std::vector< std::vector< std::vector<int> > >	&map, int width, int height);	
//zappy cmd from server:
		void											msz(void);
		void											bct(void);
};
#endif
