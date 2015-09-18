#include "SpriteTypeCollectionQueue.h"



const int SpriteTypeCollectionQueue::SIZE = 100;



SpriteTypeCollectionQueue::SpriteTypeCollectionQueue()
{
	for (int i = 0; i < SIZE; i++)
	{
		SpriteType spriteType = (SpriteType)(rand() % NUMBER_OF_AI_SPRITE_TYPES);
		distribution[spriteType]++;
		push(spriteType);
	}
}



void SpriteTypeCollectionQueue::collect(SpriteType spriteType)
{
	distribution[front()]--;
	pop();

	distribution[spriteType]++;
	push(spriteType);
}



int SpriteTypeCollectionQueue::demandFor(SpriteType spriteType)
{
	return (SIZE / NUMBER_OF_AI_SPRITE_TYPES) - distribution[spriteType];
}