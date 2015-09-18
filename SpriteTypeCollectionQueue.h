/*
Created By:
Andrew George
of Kings of Tyrants Development
http://www.KingsOfTyrants.com
Copyright 2015

License:
Commercial use of this code (or any derivative work that may come of it) is strictly prohibited.

eMotion - SpriteTypeCollectionQueue.h:
Manages queue of SpriteTypes collected by HeroSprite.
*/



#ifndef SPRITE_TYPE_COLLECTION_QUEUE_HEADER
#define SPRITE_TYPE_COLLECTION_QUEUE_HEADER



//includes
#include <queue>
#include "common.h"



class SpriteTypeCollectionQueue : public std::queue<SpriteType>
{
public:
	//size of the collection
	static const int SIZE;


	//
	SpriteTypeCollectionQueue();


	//
	void collect(SpriteType spriteType);


	//
	int demandFor(SpriteType spriteType);


private:
	//the number of each type of Sprite Type
	int distribution[NUMBER_OF_AI_SPRITE_TYPES];
};



#endif