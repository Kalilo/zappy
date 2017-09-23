#include "engine.hpp"

engine::engine(void)
{
	//this->connector();//tries to call its constructor...
}

engine::~engine(void)
{
}

server	&engine::getconnector(void)
{
	return (this->connector);
}

map		&engine::getmapper(void)
{
	return (this->mapper);
}
