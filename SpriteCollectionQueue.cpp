#include "MasterHeader.h"
#include "SpriteCollectionQueue.h"
#include "Sprite.h"



void SpriteCollectionQueue::enqeue(Type enqueueType)
{
	/* --- changing counts --- */
	Type dequeueType = collection[pointer];
	distribution[dequeueType]--;
	distribution[enqueueType]++;



	/* --- replacing dequeueType with enqueueType --- */
	collection[pointer] = enqueueType;



	if (++pointer == QUEUE_SIZE) pointer = 0;
}



Type SpriteCollectionQueue::peek()
{
	return collection[pointer];
}



int SpriteCollectionQueue::typeDemand(Type spriteType)
{
	return QUEUE_SIZE / 5 - distribution[spriteType];
}



SpriteCollectionQueue::SpriteCollectionQueue() : pointer(0)
{
	for (int i = 0; i < 5; i++)
		distribution[i] = 0;



	for (int i = 0; i < QUEUE_SIZE; i++)
	{
		Type type = Type(rand() % 5);		

		collection[i] = type;

		distribution[type]++;
	}
}