#include "map.hpp"
#include "engine.hpp"

engine	&e(void);

map::map(void)
{
}

map::~map(void)
{
}

std::vector< std::vector< std::vector<int> > >	&map::getmap(void)
{
	return (this->map_);
}

std::vector< std::vector< std::vector<int> > >		&map::initialize_map(std::vector< std::vector< std::vector<int> > > &map, int width, int height)
{
	int		x;
	int		y;
	int		z;

	z = -1;
	while (++z < (int)9 && (y = -1))
	{
		printf("debug %d\n", z);
		while (++y < height && (x = -1))
		{
			map[z].push_back(std::vector<int>(width));
			while (++x < width)
				map[z][y][x] = 0;
		}
	}
	printf("debug\n");
	return (map);
}


int		map::print_map(int mapid)
{
	int	x;
	int	y;

	y = -1;
	while (++y < (int)this->map_[mapid].size() && (x = -1))
	{
		while (++x < (int)this->map_[mapid][0].size())
			std::cout << this->map_[mapid][y][x];
		std::cout << std::endl;//may fail
	}
	return (0);
}

std::vector< std::vector< std::vector<int> > >  &map::generate_map(std::vector< std::vector< std::vector<int> > >	&map, int width, int height)
{
	int		x;

	x = -1;
	// std::vector< std::vector< std::vector<int> > >	t;
	printf("DEBUG MAP\n");

	 while (++x < 9)
		map.push_back(std::vector< std::vector<int> >());
	this->initialize_map(map, width, height);//initialize_map
//	this->print_map(0);//for debugging...
	return (map);
}

void	map::msz(void)
{
	char	*t;
	//hyuj7nmuj
	if ((t = strstr(e().getconnector().getline(), "msz ")))//msz
		e().getmapper().getmap() = e().getmapper().generate_map(e().getmapper().getmap(), atoi(&t[4]), atoi(strstr(&t[4], " ")));
}

void	map::bct(void)
{
	int		i;
	int		j;
	char	*t;
	int		var[9];

	i = -1;
	j = -1;
	if ((t = strstr(e().getconnector().getline(), "bct ")))//msz
	{
		printf("%s\n", t);
		//place at correct position of map the correct number
		while (t[++i])//loop through string
			if (t[i] == ' ')
				var[++j] = atoi(&t[i]);
	//food:
		this->map_[1][var[1]][var[0]] = var[8];
	//stones:
		this->map_[2][var[1]][var[0]] = var[2];
		this->map_[3][var[1]][var[0]] = var[3];
		this->map_[4][var[1]][var[0]] = var[4];
		this->map_[5][var[1]][var[0]] = var[5];
		this->map_[6][var[1]][var[0]] = var[6];
		this->map_[7][var[1]][var[0]] = var[7];
	}
}
