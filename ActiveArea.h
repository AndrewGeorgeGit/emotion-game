#include "MasterHeader.h"



#ifndef ACTIVE_AREA_HEADER
#define ACTIVE_AREA_HEADER



//Responsible for 
//Class responsible for containing sprites
class ActiveArea
{
public:
	//1 for the user, 10 for the initial number spawned, 10 for an expected upperbound
	//whenever a Sprite "dies", it has the option of generating 0, 1, or 2 more. Reasonable, this fact should keep the total number of Sprites around 10.
	//But just in case if all decide to spontaneously spawn 2, an upperbound of 10 + 10 is assumed.
	//12345comment: make movement more smooth by linking it to time?
	static const int MAX_SPRITES = 81;


	//the min/max coordinate values surrounding the Active Area
	static const int MIN_X, MAX_X, MIN_Y, MAX_Y, SIZE;


	//returns singleton
	static ActiveArea* getActiveArea();


	//attempts to add a Sprite to the ActiveArea. It will not if there are a maximum number of Sprites already.
	//Returns true if Sprite was added. False if the maximum has already been reached and no Sprite was added.
	//12345comment: comment better, seeing about keeping alphabethical order.
	bool addSprite(Type spriteType = Type::INVALID_TYPE);
	void removeSprite(int index);


	//
	void play();


private:
	//constructor that intializes the single active area intance by filling sprites with null pointers
	ActiveArea();


	//only one ActiveArea is necesary
	static ActiveArea *singleton;	//12345comment: do you delete?


	//array that holds pointers dynamically create Sprites up to a maximum
	//the Sprites will remained order (see Sprite.h for more information)
	Sprite *sprites[MAX_SPRITES];


	//how many of each type there are
	int distribution[5];


	//the number of Sprites in the active area
	int spriteCount;


	//
	Type determineNewSpriteType();


	//
	void order();
};



#endif