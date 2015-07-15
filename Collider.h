#include "MasterHeader.h"



#ifndef COLLIDER_HEADER
#define COLLIDER_HEADER



class Collider
{
public:
	//
	Collider(Sprite* sprites[], int count);


private:
	//holds vectors of sprites which have collided with each other
	std::vector<Collision> collisions;


	//
	int *collisionGroupIndex;
};



#endif
