#include "MasterHeader.h"



#ifndef SPRITE_COLLECTION_QUEUE_HEADER
#define SPRITE_COLLECTION_QUEUE_HEADER



//12345comment: refactor to make more OOP-focused
class SpriteCollectionQueue
{
public:
	//fills collection and tallys distrubtion, points pointer to the first element
	SpriteCollectionQueue();


	//the number of Sprites the hero can collect
	//should be a multiple of 5 to allow for the win condition of even distribution between all Types
	static const int QUEUE_SIZE = 100;


	//dequeues Type in front of queue and adds passed Type to the back of the queue
	void enqeue(Type type);


	//returns the type that will be dequeued next
	Type peek();


	//the amout of a particular type of sprite that must be gained/lost to be suitable for victory
	int typeDemand(Type spriteType);


private:
	//holds the order the hero has collected Sprites
	Type collection[QUEUE_SIZE];


	//how much of each type of Sprite the hero has collected
	int distribution[5];


	//the index value of where the front of the queue is in collection
	int pointer;
};


#endif